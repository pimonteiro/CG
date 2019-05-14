#ifndef __PLANE_H__
#define __PLANE_H__

#include <string>
#include <vector>
#include "../../lib/headers/point.h"

std::string plane(float, float, float, float, float, int, int);
void planeCoords(float, float, float, float, float, int, int, std::vector<Point *> *);
void planeTexture(int, int, int, int, std::vector<Point *> *);
#endif
