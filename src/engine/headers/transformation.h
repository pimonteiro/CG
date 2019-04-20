#ifndef __TRANSFORMATION_H__
#define __TRANSFORMATION_H__

#include "../../lib/headers/point.h"

class Transformation {
    private:
        Point v;
    public:
        Transformation(Point);
        virtual ~Transformation();
        virtual void transform() = 0;
        Point V() {
                return v;
        }
};

#endif
