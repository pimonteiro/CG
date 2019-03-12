#ifndef __SCALE_H__
#define __SCALE_H__

#include "transformation.h"

class Scale: public Transformation {
    public:
        Scale(Point);
        void transform();
};


#endif