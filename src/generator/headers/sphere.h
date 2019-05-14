#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <string>
#include <vector>
#include "../../lib/headers/point.h"

std::string sphere(float, int, int);

void sphereCoords(float, int, int, std::vector<Point *> *);
void sphereTexture(int, int, std::vector<Point *> *);

#endif
