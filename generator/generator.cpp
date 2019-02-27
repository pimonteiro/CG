#include <iostream>
#include <cstring>
#include "box.h"


// Display usage of program
// generator box 5 5 5 1 box.3d
void helpMessage(){
    std::cout << "1) generator plane <x-dim> <z-dim>" << std::endl;
    std::cout << "2) generator box <x-dim> <y-dim> <z-dim> <slices (optional)> <filename>" << std::endl;
    std::cout << "3) generator sphere <radius> <slices> <stacks> <filename>" << std::endl;
    std::cout << "4) generator cone <bottom radius> <height> <slices> <stacks> <filename>" << std::endl;
}

void coneHandling(int argc, char* pString[]) {

}

void sphereHandling(int argc, char* pString[]) {

}

void planeHandling(int argc, char* pString[]) {

}

void boxHandling(int argc, char* pString[]) {
    if(argc < 6) { //Must have 6 minimum parameters (1 optional)
        std::cerr << "Insufficient parameters.\nNeeded: x-dim, y-dim, z-dim, number of divisions, file to write" << std::endl;
    }
    else {
        int div;
        if(argc == 6)
            div = 1;
        else
            div = std::stoi(pString[5]);

        float xDim = std::stof(pString[2]);
        float yDim = std::stof(pString[3]);
        float zDim = std::stof(pString[4]);
        box(xDim,yDim,zDim,div,pString[6]);
    }
}

int main(int argc, char* argv[]) {

    if(argc < 2) {
        std::cerr << "Use --help for more information of how to use." << std::endl;
    }
    else {
        if(strcmp("--help", argv[1])) {
            helpMessage();
        }
        else {
            if(strcmp("box",argv[1])) {
                boxHandling(argc,argv);
            }
            else if(strcmp("plane",argv[1])) {
                planeHandling(argc,argv);
            }
            else if(strcmp("sphere",argv[1])) {
                sphereHandling(argc,argv);
            }
            else if(strcmp("cone",argv[1])) {
                coneHandling(argc,argv);
            }
            else {
                std::cerr << "Invalid parameters. Check with --help for usage examples." << std::endl;
            }
        }
    }
    return 0;
}