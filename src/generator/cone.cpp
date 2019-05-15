#include "headers/cone.h"
#include "headers/outputAux.h"
#include "../lib/headers/point.h"
#include "headers/normal.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>

void frustum(float radiusBottom, float radiusTop, float slices, float alpha, float dHeight, float yB, int isFirst, std::vector<Point *> *points) {
        for (int i {0}; i < slices; i++) {
                double x1b {radiusBottom * sin(i * alpha)};
                double z1b {radiusBottom * cos(i * alpha)};
                double x2b {radiusBottom * sin((i + 1)*alpha)};
                double z2b {radiusBottom * cos((i + 1)*alpha)};
                double x1t {radiusTop * sin(i * alpha)};
                double z1t {radiusTop * cos(i * alpha)};
                double x2t {radiusTop * sin((i + 1)*alpha)};
                double z2t {radiusTop * cos((i + 1)*alpha)};
                double yT {yB + dHeight};
                // left triangle
                points->push_back(new  Point(x1b, yB, z1b)); // 1
                points->push_back(new  Point(x2t, yT, z2t)); // 2
                points->push_back(new  Point(x1t, yT, z1t)); // 3
                // right triangle
                points->push_back(new  Point(x1b, yB, z1b)); // 1
                points->push_back(new  Point(x2b, yB, z2b)); // 4
                points->push_back(new  Point(x2t, yT, z2t)); // 2

                if (isFirst) {
                        points->push_back(new  Point(0, 0, 0)); // bottom center
                        points->push_back(new  Point(x2b, 0, z2b)); // 4
                        points->push_back(new  Point(x1b, 0, z1b)); // 1
                }
        }
}


void coneCoords(float radius, float height, int slices, int stacks, std::vector<Point *> *points) {
        if (radius <= 0.0f || slices <= 0 || stacks <= 0)
                std::cerr << "All parameters must be positive numbers\n";

        double alpha {2 * M_PI / slices};
        double dHeight {height / stacks};
        double yB {0};
        double yT {height / stacks};
        double radiusBottom {radius};
        float radiusTop;
        int isFirst;

        for (int j {stacks}; j > 0; j--) {
                radiusTop = (j - 1) * radius / stacks;
                isFirst = !(stacks - j);
                frustum(radiusBottom, radiusTop, slices, alpha, dHeight, yB, isFirst, points);
                radiusBottom = radiusTop;
                yB = yT;
                yT += dHeight;
        }
}

std::string cone(float radius, float height, int slices, int stacks) {
        std::ostringstream os;
        std::vector<Point *> points, pNormals, pTextures;
        coneCoords(radius, height, slices, stacks, &points);
        calculateNormals(points, &pNormals);

        int nn {static_cast<int>(points.size())};
        for (int i {0}; i < nn; i++)
                pTextures.push_back(new Point(0, 0, 0));

        os << points.size() << std::endl;
        os << writeVector(points) << writeVector(pNormals) << writeTextVector(pTextures);
        return os.str();
}
