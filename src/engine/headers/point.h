#ifndef __POINT_H__
#define __POINT_H__

#include <string>

class Point {
  private:
    float x,y,z;
  public:
    Point();
    Point(float, float, float);

    float X() {
        return x;
    }
    float Y() {
        return y;
    }
    float Z() {
        return z;
    }
};

#endif
