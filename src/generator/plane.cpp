#include <sstream>
#include <vector>
#include "headers/plane.h"
#include "headers/outputAux.h"
#include "../lib/headers/point.h"
#include "headers/normal.h"

void planeCoords(float xO, float yO, float zO, float xP, float zP, int type, int place, std::vector<Point> *points) {
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
                points->push_back(Point(-x + xO, y + yO, z + zO)); // 1
                points->push_back(Point(x + xO, flag * y + yO, z + zO)); // 2
                points->push_back(Point(x + xO, -y + yO, -z + zO)); // 3
                points->push_back(Point(-x + xO, y + yO, z + zO)); // 1
                points->push_back(Point(x + xO, -y + yO, -z + zO)); // 3
                points->push_back(Point(-x + xO, -flag * y + yO, -z + zO)); // 4
        } else if (place == 0) {
                // trás
                points->push_back(Point(x + xO, -y + yO, -z + zO)); // 3
                points->push_back(Point(x + xO, flag * y + yO, z + zO)); // 2
                points->push_back(Point(-x + xO, y + yO, z + zO)); // 1
                points->push_back(Point(-x + xO, -flag * y + yO, -z + zO)); // 4
                points->push_back(Point(x + xO, -y + yO, -z + zO)); // 3
                points->push_back(Point(-x + xO, y + yO, z + zO)); // 1
        }
}


std::string plane(float xO, float yO, float zO, float xP, float zP, int type, int place) {
        std::ostringstream os;
        os << "6\n";
        std::vector<Point> points;
        planeCoords(xO, yO, zO, xP, zP, type, place, &points);
        std::vector<Point> pp;
        calculateNormals(points, &pp);
        // Missing textures!
        os << writeVector(points);
        os << writeVector(pp);
        return os.str();
}
