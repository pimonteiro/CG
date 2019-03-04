#ifndef __MODEL_H__
#define __MODEL_H__

#include <string>
#include <vector>
#include "point.h"

class  Model {
    std::vector<Point*> pointsV;
  public:
    Model();
    void addElement(Point*);
    std::vector<Point*> model();
    void draw();
};
#endif