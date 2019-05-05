#ifndef __BOX_H__
#define __BOX_H__

#include <string>
#include <vector>
#include "../../lib/headers/point.h"

std::string box(float, float, int);
void boxCoords(float, float, int, std::vector<Point *> *);

#endif
