#ifndef __ROTATION_H__
#define __ROTATION_H__

#include "transformation.h"

class Rotation: public Transformation {
    private:
        float angle, time;
    public:
        Rotation(Point, float, float);
        ~Rotation();
        void transform();
};

#endif
