#include <sstream>
#include <vector>
#include "headers/plane.h"
#include "headers/outputAux.h"
#include "../lib/headers/point.h"
#include "headers/normal.h"

void planeCoords(float xO, float yO, float zO, float xP, float zP, int type, int place, std::vector<Point *> *points) {
        float x, y, z;
        x = xP / 2;
        y = 0;
        z = zP / 2;
        float flag {1};

        if (type == 1) {
                y = -z;
                z = 0;
        } else if (type == 2) {
                y = x;
                x = 0;
                flag = -1;
        }

        if (place == 1) {
                // frente
                points->push_back(new Point(-x + xO, y + yO, z + zO)); // 1
                points->push_back(new Point(x + xO, flag * y + yO, z + zO)); // 2
                points->push_back(new Point(x + xO, -y + yO, -z + zO)); // 3
                points->push_back(new Point(-x + xO, y + yO, z + zO)); // 1
                points->push_back(new Point(x + xO, -y + yO, -z + zO)); // 3
                points->push_back(new Point(-x + xO, -flag * y + yO, -z + zO)); // 4
        } else if (place == 0) {
                // trás
                points->push_back(new Point(x + xO, -y + yO, -z + zO)); // 3
                points->push_back(new Point(x + xO, flag * y + yO, z + zO)); // 2
                points->push_back(new Point(-x + xO, y + yO, z + zO)); // 1
                points->push_back(new Point(-x + xO, -flag * y + yO, -z + zO)); // 4
                points->push_back(new Point(x + xO, -y + yO, -z + zO)); // 3
                points->push_back(new Point(-x + xO, y + yO, z + zO)); // 1
        }
}

void planeTexture(int xS, int yS, int div, int place, std::vector<Point *> *textPoints) {
        float step {1.0f / div};

        if (place == 1) {
                textPoints->push_back(new Point(xS, yS, 0));
                textPoints->push_back(new Point(xS + step, yS, 0));
                textPoints->push_back(new Point(xS + step, yS + step, 0));
                textPoints->push_back(new Point(xS, yS, 0));
                textPoints->push_back(new Point(xS + step, yS + step, 0));
                textPoints->push_back(new Point(xS, yS + step, 0));
        } else if (place == 0) {
                textPoints->push_back(new Point(xS, yS, 0));
                textPoints->push_back(new Point(xS + step, yS + step, 0));
                textPoints->push_back(new Point(xS + step, yS, 0));
                textPoints->push_back(new Point(xS, yS, 0));
                textPoints->push_back(new Point(xS, yS + step, 0));
                textPoints->push_back(new Point(xS + step, yS + step, 0));
        }
}

std::string plane(float xO, float yO, float zO, float xP, float zP, int type, int place) {
        std::ostringstream os;
        os << "6\n";
        std::vector<Point *> points, normPoints, textPoints;
        planeCoords(xO, yO, zO, xP, zP, type, place, &points);
        calculateNormals(points, &normPoints);
        planeTexture(0, 0, place, 1, &textPoints);
        os << writeVector(points);
        os << writeVector(normPoints);
        os << writeTextVector(textPoints);
        return os.str();
}
