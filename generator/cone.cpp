#include "cone.h"
#include "outputAux.h"
#include <iostream>
#include <sstream>
#include <cmath>

std::string frustum(float radiusBottom, float radiusTop, float slices, float alpha, float dHeight, float yB, int* nPoints, int isFirst) {

    std::ostringstream os;

    for(int i {0}; i < slices; i++) {

        double x1b {radiusBottom * sin(i*alpha)};
        double z1b {radiusBottom * cos(i*alpha)};
        double x2b {radiusBottom * sin((i+1)*alpha)};
        double z2b {radiusBottom * cos((i+1)*alpha)};

        double x1t {radiusTop * sin(i*alpha)};
        double z1t {radiusTop * cos(i*alpha)};
        double x2t {radiusTop * sin((i+1)*alpha)};
        double z2t {radiusTop * cos((i+1)*alpha)};

        double yT {yB + dHeight};

        // left triangle
        os << writePoint(x1b,yB,z1b); // 1
        os << writePoint(x2t,yT,z2t); // 2
        os << writePoint(x1t,yT,z1t); // 3

        // right triangle
        os << writePoint(x1b,yB,z1b); // 1
        os << writePoint(x2b,yB,z2b); // 4
        os << writePoint(x2t,yT,z2t); // 2

        *nPoints += 6;

        if (!isFirst) {
            os << writePoint(0,0,0); // bottom center
            os << writePoint(x2b,0,z2b); // 4
            os << writePoint(x1b,0,z1b); // 1
            *nPoints += 3;
        }

    }

    return os.str();

}

void cone(float radius, float height, int slices, int stacks, const std::string& file) {

    if(radius <= 0.0f || slices <= 0 || stacks <= 0) {
        std::cerr << "All parameters must be positive numbers\n";
    }

    std::ostringstream os;

    double alpha {2*M_PI/slices};
    double dHeight {height/stacks};
    double yB {0};
    double yT {height/stacks};
    double radiusBottom {radius};
    int nPoints {0};
    float radiusTop;
    int isFirst;

    for(int j {stacks}; j >= 0; j--) {
        radiusTop = j* radius/stacks;
        isFirst = !(stacks - j);
        os << frustum(radiusBottom, radiusTop, slices, alpha, dHeight, yB, &nPoints, isFirst);
        radiusBottom = radiusTop;
        yB = yT;
        yT += dHeight;
    }

    dumpFile(nPoints, os, file);
    
}
