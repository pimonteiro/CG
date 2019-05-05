#include "headers/sphere.h"
#include "headers/outputAux.h"
#include "headers/normal.h"
#include "../lib/headers/point.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>


Point trans(float, float, float);

void sphereCoords(float radius, int slices, int stacks, std::vector<Point> *points) {
        if (radius <= 0.0f || slices <= 0 || stacks <= 0)
                fputs("All parameters must be positive numbers\n", stderr);

        float deltaAlpha { static_cast<float>(2.0f * M_PI / slices) };
        float deltaBeta { static_cast<float>(M_PI / stacks) };

        for (int i {0}; i < stacks; i++) {
                float beta {i * deltaBeta};
                float nextBeta {beta + deltaBeta};

                for (int j {0}; j < slices; j++) {
                        float alpha {j * deltaAlpha};
                        float nextAlpha {alpha + deltaAlpha};

                        if (i < stacks - 1) {
                                points->push_back(trans(beta, alpha, radius));
                                points->push_back(trans(nextBeta, alpha, radius));
                                points->push_back(trans(nextBeta, nextAlpha, radius));
                        }

                        if (i > 0) {
                                points->push_back(trans(beta, alpha, radius));
                                points->push_back(trans(nextBeta, nextAlpha, radius));
                                points->push_back(trans(beta, nextAlpha, radius));
                        }
                }
        }
}


std::string sphere(float radius, int slices, int stacks) {
        std::ostringstream os;
        std::vector<Point> points, pNormals;
        sphereCoords(radius, slices, stacks, &points);
        calculateNormals(points, &pNormals);
        os << points.size() << std::endl;
        os << writeVector(points) << writeVector(pNormals);
        return os.str();
}

Point trans(float a, float b, float c) {
        return Point(c * sinf(a) * sinf(b), c * cosf(a), c * sinf(a) * cosf(b));
}
