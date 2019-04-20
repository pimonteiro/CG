#include "headers/sphere.h"
#include "headers/outputAux.h"
#include <iostream>
#include <sstream>
#include <cmath>


std::string trans(float, float, float);

std::string sphere(float radius, int slices, int stacks) {
        if (radius <= 0.0f || slices <= 0 || stacks <= 0)
                fputs("All parameters must be positive numbers\n", stderr);

        std::ostringstream os;
        int nPoints {0};
        float deltaAlpha { static_cast<float>(2.0f * M_PI / slices) };
        float deltaBeta { static_cast<float>(M_PI / stacks) };

        for (int i {0}; i < stacks; i++) {
                float beta {i * deltaBeta};
                float nextBeta {beta + deltaBeta};

                for (int j {0}; j < slices; j++) {
                        float alpha {j * deltaAlpha};
                        float nextAlpha {alpha + deltaAlpha};

                        if (i < stacks - 1) {
                                os << trans(beta, alpha, radius);
                                os << trans(nextBeta, alpha, radius);
                                os << trans(nextBeta, nextAlpha, radius);
                                nPoints += 3;
                        }

                        if (i > 0) {
                                os << trans(beta, alpha, radius);
                                os << trans(nextBeta, nextAlpha, radius);
                                os << trans(beta, nextAlpha, radius);
                                nPoints += 3;
                        }
                }
        }

        std::ostringstream r;
        r << nPoints << '\n' << os.str();
        return r.str();
}

std::string trans(float a, float b, float c) {
        return writePoint(c * sinf(a) * sinf(b), c * cosf(a), c * sinf(a) * cosf(b));
}
