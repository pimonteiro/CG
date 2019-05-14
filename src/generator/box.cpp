#include <sstream>
#include <vector>
#include "headers/box.h"
#include "headers/plane.h"
#include "headers/normal.h"
#include "headers/outputAux.h"
#include "../lib/headers/point.h"
#include <regex>

void boxCoords(float xP, float zP, int div, std::vector<Point *> *points) {
        double dz  {zP / (2 * div)};
        double zO  {-zP / 2 + dz};
        double dx  {xP / (2 * div)};
        double xO, auxO;

        for (int j {0}; j < div; j++) {
                xO = -xP / 2 + dx;
                auxO = -zP / 2 + dz;

                for (int i {0}; i < div; i++) {
                        planeCoords(xO, zP / 2, zO, 2 * dx, 2 * dz, 0, 1, points); // cima
                        planeCoords(xO, -zP / 2, zO, 2 * dx, 2 * dz, 0, 0, points); // baixo
                        planeCoords(xO, zO, zP / 2, 2 * dx, 2 * dz, 1, 1, points); // frente
                        planeCoords(xO, zO, -zP / 2, 2 * dx, 2 * dz, 1, 0, points); // trás
                        planeCoords(xP / 2, zO, auxO, 2 * dz, 2 * dz, 2, 1, points); // direita
                        planeCoords(-xP / 2, zO, auxO, 2 * dz, 2 * dz, 2, 0, points); // esquerda
                        xO += 2 * dx;
                        auxO += 2 * dz;
                }

                zO += 2 * dz;
        }
}

void boxTexture(int div, std::vector<Point *> *pTexture) {
        for (int r {0}; r < 3; r++) {
                for (int ori {0}; ori < 2; ori++) {
                        for (int i {0}; i < div; i++) {
                                float u {static_cast<float>(i / div)};

                                for (int j {0}; j < div; j++) {
                                        float v {static_cast<float>(j / div)};
                                        planeTexture(u, v, div, !ori, pTexture);
                                }
                        }
                }
        }
}


std::string box(float xP, float zP, int div) {
        std::ostringstream os, r;
        std::vector<Point *> points, pNormals, pTexture;
        boxCoords(xP, zP, div, &points);
        calculateNormals(points, &pNormals);
        boxTexture(div, &pTexture);
        os << points.size() << std::endl;
        os << writeVector(points) << writeVector(pNormals) << writeTextVector(pTexture);
        return os.str();
}
