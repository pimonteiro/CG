#ifndef __MODEL_H__
#define __MODEL_H__

#include <string>
#include <vector>
#include "point.h"

class  Model {
    std::vector<Point*> pointsV;
    std::vector<Point*> colorsV;
  public:
    Model();
    void addElement(Point*);
    void addColor(Point*);
    std::vector<Point*> model();
    void draw();
};
#endif
