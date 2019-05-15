#include <sstream>
#include "headers/annulus.h"
#include "headers/outputAux.h"
#include "headers/normal.h"
#include "../lib/headers/point.h"
#include <cmath>
#include <vector>


void annulusCoords(float innerRadius, float outerRadius, float height, int div, std::vector<Point *> *points) {
        float angle {static_cast<float>(2 * M_PI / div) };
        float h { height / 2 };

        for (int i {0}; i < div; i++) {
                float alpha { static_cast<float>(angle * i) };
                points->push_back(new Point(cos(alpha)*innerRadius, h, sin(alpha)*innerRadius));
                points->push_back(new Point(cos(angle * (i + 1))*innerRadius, h, sin(angle * (i + 1))*innerRadius));
                points->push_back(new Point(cos(alpha)*outerRadius, h, sin(alpha)*outerRadius));
                points->push_back(new Point(cos(alpha)*outerRadius, h, sin(alpha)*outerRadius));
                points->push_back(new Point(cos(angle * (i + 1))*innerRadius, h, sin(angle * (i + 1))*innerRadius));
                points->push_back(new Point(cos(angle * (i + 1))*outerRadius, h, sin(angle * (i + 1))*outerRadius));
                points->push_back(new Point(cos(alpha)*innerRadius, -h, sin(alpha)*innerRadius));
                points->push_back(new Point(cos(alpha)*outerRadius, -h, sin(alpha)*outerRadius));
                points->push_back(new Point(cos(angle * (i + 1))*innerRadius, -h, sin(angle * (i + 1))*innerRadius));
                points->push_back(new Point(cos(alpha)*outerRadius, -h, sin(alpha)*outerRadius));
                points->push_back(new Point(cos(angle * (i + 1))*outerRadius, -h, sin(angle * (i + 1))*outerRadius));
                points->push_back(new Point(cos(angle * (i + 1))*innerRadius, -h, sin(angle * (i + 1))*innerRadius));
                points->push_back(new Point(cos(alpha)*innerRadius, h, sin(alpha)*innerRadius));
                points->push_back(new Point(cos(alpha)*innerRadius, -h, sin(alpha)*innerRadius));
                points->push_back(new Point(cos(angle * (i + 1))*innerRadius, h, sin(angle * (i + 1))*innerRadius));
                points->push_back(new Point(cos(angle * (i + 1))*innerRadius, -h, sin(angle * (i + 1))*innerRadius));
                points->push_back(new Point(cos(angle * (i + 1))*innerRadius, h, sin(angle * (i + 1))*innerRadius));
                points->push_back(new Point(cos(alpha)*innerRadius, -h, sin(alpha)*innerRadius));
                points->push_back(new Point(cos(alpha)*outerRadius, h, sin(alpha)*outerRadius));
                points->push_back(new Point(cos(angle * (i + 1))*outerRadius, h, sin(angle * (i + 1))*outerRadius));
                points->push_back(new Point(cos(alpha)*outerRadius, -h, sin(alpha)*outerRadius));
                points->push_back(new Point(cos(angle * (i + 1))*outerRadius, -h, sin(angle * (i + 1))*outerRadius));
                points->push_back(new Point(cos(alpha)*outerRadius, -h, sin(alpha)*outerRadius));
                points->push_back(new Point(cos(angle * (i + 1))*outerRadius, h, sin(angle * (i + 1))*outerRadius));
        }
}

std::string annulus(float innerRadius, float outerRadius, float height, int div) {
        std::ostringstream os;
        std::vector<Point *> points, pNormals, pTextures;
        annulusCoords(innerRadius, outerRadius, height, div, &points);
        calculateNormals(points, &pNormals);
        for(int i = 0; i < points.size(); i++){
            pTextures.push_back(new Point(0,0,0));
        }

        os << points.size() << std::endl;
        os << writeVector(points) << writeVector(pNormals) << writeTextVector(pTextures);
        return os.str();
}
