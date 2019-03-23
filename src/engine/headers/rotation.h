#ifndef __ROTATION_H__
#define __ROTATION_H__

#include "transformation.h"

class Rotation: public Transformation {
    private:
        float angle;
    public:
        Rotation(Point,float);
        ~Rotation();
        void transform();
};

#endif