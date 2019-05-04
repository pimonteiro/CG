#include <sstream>
#include <vector>
#include "headers/plane.h"
#include "headers/outputAux.h"
#include "../lib/headers/point.h"
#include "headers/normal.h"


std::string plane(float xO, float yO, float zO, float xP, float zP, int type, int place) {
        std::ostringstream os;
        std::vector<float> points;
        os << "6\n";
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
                points.push_back(-x + xO);
                points.push_back(y + yO);
                points.push_back(z + zO); // 1
                points.push_back(x + xO);
                points.push_back(flag * y + yO);
                points.push_back(z + zO); // 2
                points.push_back(x + xO);
                points.push_back(-y + yO);
                points.push_back(-z + zO); // 3
                points.push_back(-x + xO);
                points.push_back(y + yO);
                points.push_back(z + zO); // 1
                points.push_back(x + xO);
                points.push_back(-y + yO);
                points.push_back(-z + zO); // 3
                points.push_back(-x + xO);
                points.push_back(-flag * y + yO);
                points.push_back(-z + zO); // 4
        } else if (place == 0) {
                // trás
                points.push_back(x + xO);
                points.push_back(-y + yO);
                points.push_back(-z + zO); // 3
                points.push_back(x + xO);
                points.push_back(flag * y + yO);
                points.push_back(z + zO); // 2
                points.push_back(-x + xO);
                points.push_back(y + yO);
                points.push_back(z + zO); // 1
                points.push_back(-x + xO);
                points.push_back(-flag * y + yO);
                points.push_back(-z + zO); // 4
                points.push_back(x + xO);
                points.push_back(-y + yO);
                points.push_back(-z + zO); // 3
                points.push_back(-x + xO);
                points.push_back(y + yO);
                points.push_back(z + zO); // 1
        }

        std::vector<Point> pp;
        for(std::vector<float>::iterator ptr = points.begin(); ptr < points.end();){
            float x = *ptr++;
            float y = *ptr++;
            float z = *ptr++;
            os << writePoint(x,y,z);
            pp.push_back(Point(x,y,z));
        }
        points.clear();
        calculateNormals(pp, &points);

        for(std::vector<float>::iterator ptr = points.begin(); ptr < points.end();){
            float x = *ptr++;
            float y = *ptr++;
            float z = *ptr++;
            os << writePoint(x,y,z);
        }

        //Missing textures!
        return os.str();
}
