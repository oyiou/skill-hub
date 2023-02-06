cmake_minimum_required(VERSION 3.22)
project(primer
        VERSION 1.0
        DESCRIPTION "C++ primer project"
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 14)

MACRO(SUBDIRECTORY result CurrentDir)
    FILE(GLOB children RELATIVE ${CurrentDir} ${CurrentDir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${CurrentDir}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO(SUBDIRECTORY)
SUBDIRECTORY(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)

foreach(EXAMPLE ${SUBDIRS})
    string(REPLACE "-" ";" Name ${EXAMPLE})
    list(GET Name 1 FILE)
    unset(TARGET_SOURCES)
    aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/${EXAMPLE} TARGET_SOURCES)
    aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/include/${EXAMPLE} TARGET_SOURCES)
    add_executable(${FILE}
            ${TARGET_SOURCES}
            )
    set(TARGET_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src/${EXAMPLE})
    target_include_directories(${FILE}
            PRIVATE ${INCLUDE_DIRS}
            PRIVATE ${TARGET_INCLUDE_DIRS}
            )
    set_target_properties(${FILE} PROPERTIES
            CMAKE_DEBUG_POSTFIX         "_d"
            ARCHIVE_OUTPUT_DIRECTORY    "${CMAKE_CURRENT_SOURCE_DIR}/bin/${FILE}/lib"
            LIBRARY_OUTPUT_DIRECTORY    "${CMAKE_CURRENT_SOURCE_DIR}/bin/${FILE}/lib"
            RUNTIME_OUTPUT_DIRECTORY    "${CMAKE_CURRENT_SOURCE_DIR}/bin/${FILE}/bin"
            )
endforeach(EXAMPLE)