#ifndef __ROTATION_H__
#define __ROTATION_H__

#include "transformation.h"

class Rotation: public Transformation {
    private:
        float angle;
    public:
        Rotation(Point,float);
        void transform();
        float getAngle(){
            return angle;
        }
};

#endif