#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "../../lib/headers/point.h"

#define UNDEF           -1
#define POINT           0
#define DIRECTIONAL     1
#define SPOT            2

class Light {
    private:
        int type;
        Point p;
        int i;
    public:
        Light(int, Point);
        ~Light();
        void addIndex(int);
        void draw();
};

#endif