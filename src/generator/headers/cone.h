#ifndef __CONE_H__
#define __CONE_H__

#include <string>
#include <vector>
#include "../../lib/headers/point.h"

std::string cone(float, float, int, int);
void coneCoords(float, float, int, int, std::vector<Point> *);

#endif
