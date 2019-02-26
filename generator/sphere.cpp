#include "sphere.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>


std::string trans(double, double, double);

void sphere(float radius, int slices, int stacks, const std::string &file) {
    if(radius <= 0.0f || slices <= 0 || stacks <= 0) {
        fputs("All parameters must be positive numbers\n", stderr);
    }

    std::ostringstream os;
    std::ofstream outfile;

    outfile.open(file);
    if(!outfile.is_open()) {
        perror("ofstream.open");
    }

    int nPoints {0};
    double deltaAlpha {2.0f * M_PI / slices};
    double deltaBeta {M_PI / stacks};

    for(int i = 0; i < stacks; i++) {
        double beta {i * deltaBeta};
        double nextBeta {beta + deltaBeta};

        for(int j = 0; j < slices; j++) {
            double alpha {j * deltaAlpha};
            double nextAlpha {alpha + deltaAlpha};

            if(i < stacks-1) {
                os << trans(beta, alpha, radius);
                os << trans(nextBeta, alpha, radius);
                os << trans(nextBeta, nextAlpha, radius);
                nPoints += 3;
            }
            if(i > 0) {
                os << trans(beta, alpha, radius);
                os << trans(nextBeta, nextAlpha, radius);
                os << trans(beta, nextAlpha, radius);
                nPoints += 3;
            }
        }
    }

    outfile << std::to_string(nPoints) + "\n" + os.str();
    outfile.close();
}

std::string trans(double a, double b, double c) {
    std::ostringstream os;
    os << c * sinf(a) * sinf(b) << " " << c * cosf(a) << " " << c * sinf(a) * cosf(b) << '\n';
    return os.str();
}
