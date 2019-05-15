#ifndef __ANNULUS_H__
#define __ANNULUS_H__

#include <string>
#include <vector>
#include "../../lib/headers/point.h"

std::string annulus(float, float, float, int);
void annulusCoords(float, float, float, int, std::vector<Point *> *);
void annulusTexture(int , std::vector<Point *> *);

#endif
