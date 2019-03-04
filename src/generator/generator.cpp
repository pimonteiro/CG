#include <iostream>
#include <cstring>
#include <sstream>
#include "headers/box.h"
#include "headers/cone.h"
#include "headers/plane.h"
#include "headers/sphere.h"
#include "headers/outputAux.h"

using namespace std;


// Display usage of program
void helpMessage(){
    cout << "[*] ./generator plane <dim> <filename>" << endl;
    cout << "[*] ./generator box <x-dim> <y-dim> <z-dim> <slices (optional)> <filename>" << endl;
    cout << "[*] ./generator sphere <radius> <slices> <stacks> <filename>" << endl;
    cout << "[*] ./generator cone <bottom radius> <height> <slices> <stacks> <filename>" << endl;
}

string drawCone(int argc, char* pString[]) {
    if(argc != 7) {
        cerr << "Insufficient parameters." << endl;
        helpMessage();
        exit(1);
    }
    else {
        float radius { stof(pString[2]) };
        float height { stof(pString[3]) };
        int slices { stoi(pString[4]) };
        int stacks { stoi(pString[5]) };

        return cone(radius, height, slices, stacks);
    }
}

string drawSphere(int argc, char* pString[]) {
    if(argc != 6) {
        cerr << "Insufficient parameters." << endl;
        helpMessage();
        exit(1);
    }
    else {
        float radius { stof(pString[2]) };
        int slices { stoi(pString[3]) };
        int stacks { stoi(pString[4]) };

        return sphere(radius, slices, stacks);
    }
}

string drawPlane(int argc, char* pString[]) {
    if(argc != 4 ) {
        cerr << "Insufficient parameters." << endl;
        helpMessage();
        exit(1);
    }
    else {
        float x { stof(pString[2]) };

        return plane(0, 0, 0, x, x, 0, 1);
    }
}

string drawBox(int argc, char* pString[]) {
    if(!(argc == 6 || argc == 7)) { //Must have 6 minimum parameters (1 optional)
        cerr << "Insufficient parameters." << endl;
        helpMessage();
        exit(1);
    }
    else {
        int div;
        if(argc == 6)
            div = { 1 };
        else
            div = { stoi(pString[5]) };

        float xDim { stof(pString[2]) };
        float yDim { stof(pString[3]) };
        float zDim { stof(pString[4]) };
        return box(xDim,yDim,zDim,div);
    }
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        cerr << "Run with --help for more information." << endl;
    } else {
        if(!strcmp("--help", argv[1])) {
            helpMessage();
        } else {
            ostringstream os;
            if(!strcmp("box",argv[1])) {
                os << drawBox(argc, argv);
            }
            else if(!strcmp("plane",argv[1])) {
                os << drawPlane(argc, argv);
            }
            else if(!strcmp("sphere",argv[1])) {
                os << drawSphere(argc, argv);
            }
            else if(!strcmp("cone",argv[1])) {
                os << drawCone(argc,argv);
            }
            else {
                cerr << "Invalid option. Run with --help for more information." << endl;
            }
            dumpFile(os, argv[argc-1]);
        }
    }
    return 0;
}