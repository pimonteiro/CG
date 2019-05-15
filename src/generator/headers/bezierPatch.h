#ifndef __BEZIERPATCH_H__
#define __BEZIERPATCH_H__

#include <string>
#include <vector>
#include "../../lib/headers/point.h"

std::string bezierPatch(std::string, int);
void bezierTexture(int , int , std::vector<Point *> *);
#endif
