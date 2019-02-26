#include "sphere.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

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

            if(i<stacks-1) {
                os << radius * sinf(beta) * sinf(alpha) << " " << radius * cosf(beta) << " " << radius * sinf(beta) * cosf(alpha) << '\n';
                os << radius * sinf(nextBeta) * sinf(alpha) << " " << radius * cosf(nextBeta) << " " << radius * sinf(nextBeta) * cosf(alpha) << '\n';
                os << radius * sinf(nextBeta) * sinf(nextAlpha) << " " << radius * cosf(nextBeta) << " " << radius * sinf(nextBeta) * cosf(nextAlpha) << '\n';
                nPoints += 3;
            }
            if(i>0) {
                os << radius * sinf(beta) * sinf(alpha) << " " << radius * cosf(beta) << " " << radius * sinf(beta) * cosf(alpha) << '\n';
                os << radius * sinf(nextBeta) * sinf(nextAlpha) << " " << radius * cosf(nextBeta) << " "<< radius * sinf(nextBeta) * cosf(nextAlpha) << '\n';
                os << radius * sinf(beta) * sinf(nextAlpha) << " " << radius * cosf(beta) << " " << radius * sinf(beta) * cosf(nextAlpha) << '\n';
                nPoints += 3;
            }
        }

    }

    outfile << std::to_string(nPoints) + "\n" + os.str();
    outfile.close();
}
