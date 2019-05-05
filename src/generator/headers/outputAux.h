#ifndef __OUTPUTAUX_H__
#define __OUTPUTAUX_H__

#include <string>
#include <vector>
#include "../../lib/headers/point.h"

std::string writePoint(float, float, float);
void dumpFile(const std::ostringstream &, const std::string &);
<<<<<<< HEAD
std::string writeVector(std::vector<Point *>);
std::string writeTextVector(std::vector<Point *>);
=======
std::string writeVector(std::vector<Point>);
>>>>>>> a2cb27f... add generation of vertex and normal coords

#endif
