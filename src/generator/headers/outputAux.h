#ifndef __OUTPUTAUX_H__
#define __OUTPUTAUX_H__

#include <string>
#include <vector>
#include "../../lib/headers/point.h"

std::string writePoint(float, float, float);
void dumpFile(const std::ostringstream &, const std::string &);
<<<<<<< HEAD
<<<<<<< HEAD
std::string writeVector(std::vector<Point *>);
std::string writeTextVector(std::vector<Point *>);
=======
std::string writeVector(std::vector<Point>);
>>>>>>> a2cb27f... add generation of vertex and normal coords
=======
std::string writeVector(std::vector<Point>);
>>>>>>> 7336ffe9d1a776ad907f6c8054253a0b3ca324f2

#endif
