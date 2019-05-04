#ifndef __NORMAL_H__
#define __NORMAL_H__

#include "../../lib/headers/point.h"
#include <vector>

void computeNormal(Point, Point, Point, std::vector<float> *);
void calculateNormals(std::vector<Point>,std::vector<float> *);

#endif
