#include "headers/point.h"
#include <sstream>
#include <string>

Point::Point(): x(0.0f), y(0.0f), z(0.0f) {}

Point::~Point() {}

Point::Point(float x, float y, float z) : x(x), y(y), z(z) {}

Point Point::subtract(Point p){
    float x = this->x - p.X();
    float y = this->y - p.Y();
    float z = this->z - p.Z();
    Point r {Point(x,y,z)};
    return r;
}

void Point::toFloat(float p[3]){
    p[0] = this->x;
    p[1] = this->y;
    p[2] = this->z;
}
