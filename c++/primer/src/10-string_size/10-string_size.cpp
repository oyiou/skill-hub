//
// Created by leever on 6/2/2022.
//
#include "primer.h"
int main() {
    std::string line;
    while(std::getline(std::cin, line))
        if(line.size() > 80)
            std::cout << line << std::endl;
    return 0;
}