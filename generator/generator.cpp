#include <iostream>
#include <cstring>
#include "box.h"
#include "cone.h"
#include "plane.h"
#include "sphere.h"


// Display usage of program
// generator box 5 5 5 1 box.3d
void helpMessage(){
    std::cout << "1) generator plane <x-dim> <filename>" << std::endl;
    std::cout << "2) generator box <x-dim> <y-dim> <z-dim> <slices (optional)> <filename>" << std::endl;
    std::cout << "3) generator sphere <radius> <slices> <stacks> <filename>" << std::endl;
    std::cout << "4) generator cone <bottom radius> <height> <slices> <stacks> <filename>" << std::endl;
}

void coneHandling(int argc, char* pString[]) {
    if(argc < 7){
        std::cerr << "Insufficient parameters.\nNeeded: bottom radius, height, number of slices, number of stackes, file to write" << std::endl;
    }
    else {
        float radius = std::stof(pString[2]);
        float h = std::stof(pString[3]);
        int sl = std::stoi(pString[4]);
        int stacks = std::stoi(pString[5]);

        cone(radius,h,sl,stacks,pString[6]);
    }
}

void sphereHandling(int argc, char* pString[]) {
    if(argc < 6) {
        std::cerr << "Insufficient parameters.\nNeeded: radius, number of slices, number of stacks, file to write" << std::endl;
    }
    else {
        float radius = std::stof(pString[2]);
        int sl = std::stoi(pString[3]);
        int stacks = std::stoi(pString[4]);

        sphere(radius,sl,stacks,pString[5]);
    }
}

void planeHandling(int argc, char* pString[]) {
    if(argc < 5 ) {
        std::cerr << "Insufficient parameters.\nNeeded: x-dim, file to write" << std::endl;
    }
    else {
        float x = std::stof(pString[2]);

        plane(x,pString[3]);
    }

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
        if(strcmp("--help", argv[1]) == 0) {
            helpMessage();
        }
        else {
            if(strcmp("box",argv[1]) == 0) {
                boxHandling(argc,argv);
            }
            else if(strcmp("plane",argv[1]) == 0) {
                planeHandling(argc,argv);
            }
            else if(strcmp("sphere",argv[1]) == 0) {
                sphereHandling(argc,argv);
            }
            else if(strcmp("cone",argv[1]) == 0) {
                coneHandling(argc,argv);
            }
            else {
                std::cerr << "Invalid parameters. Check with --help for usage examples." << std::endl;
            }
        }
    }
    return 0;
}