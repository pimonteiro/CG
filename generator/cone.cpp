#include "cone.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>


std::string writePoint(double, double, double);

std::string frustum(float radiusBottom, float radiusTop, float slices, float alpha, float dHeight, float yB, int* nPoints) {

    std::ostringstream os;

    for(int i = 0; i < slices; i++) {

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

        if (!yB) {
            os << writePoint(0,0,0); // bottom center
            os << writePoint(x2b,0,z2b); // 4
            os << writePoint(x1b,0,z1b); // 1
            *nPoints += 3;
        }

    }

    return os.str();

}

void cone(float radius, float height, int slices, int stacks, const std::string&file) {

    if(radius <= 0.0f || slices <= 0 || stacks <= 0) {
        fputs("All parameters must be positive numbers\n", stderr);
    }

    std::ostringstream os;
    std::ofstream outfile;

    outfile.open(file);
    if(!outfile.is_open()) {
        perror("ofstream.open");
    }

    double alpha {2*M_PI/slices};
    double dHeight {height/stacks};
    double yB {0};
    double yT {height/stacks};
    double radiusBottom {radius};
    int nPoints {0};

    for(int j = stacks; j >= 0; j--) {
        float radiusTop {j* radius/stacks};
        os << frustum(radiusBottom, radiusTop, slices, alpha, dHeight, yB, &nPoints);
        radiusBottom = radiusTop;
        yB = yT;
        yT += dHeight;
    }

    outfile << std::to_string(nPoints) + "\n" + os.str();
    outfile.close();

}

std::string writePoint(double a, double b, double c) {
    std::ostringstream os;
    os << a << " " << b << " " << c << '\n';
    return os.str();
}