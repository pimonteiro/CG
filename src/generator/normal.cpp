#include "headers/normal.h"
#include "../lib/headers/matrix.h"
#include <vector>
#include <cmath>

float lengthVector(float *a) {
    float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
    return l;
}

void computeNormal(Point target, Point adj1, Point adj2, std::vector<Point> *normalVec) {
    Point p1 = target.subtract(adj1);
    Point p2 = target.subtract(adj2);

    float v1[3];
    p1.toFloat(v1);
	float v2[3];
    p2.toFloat(v2);

	float crossed[3];
	cross(v1,v2,crossed);
	normalize(crossed);
	float l = length(crossed);

    Point f {
        crossed[0]/l, crossed[1]/l, crossed[2]/l
    };
    normalVec->push_back(f);
}

void calculateNormals(std::vector<Point> points, std::vector<Point> *vec){
    for(std::vector<Point>::iterator it = points.begin(); it < points.end();){
        Point p1 = *it; it++;
        Point p2 = *it; it++;
        Point p3 = *it; it++;

        computeNormal(p1, p2, p3, vec);
        computeNormal(p2, p1, p3, vec);
        computeNormal(p3, p1, p2, vec);
    }
}
