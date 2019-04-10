#ifndef __TRANSLATION_H__
#define __TRANSLATION_H__
#include <vector>
#include "transformation.h"

class Translation: public Transformation {
    private:
        std::vector<Point *> pointV;
        float time;
    public:
        Translation();
        void addPoint(Point *);
        void addTime(float);
        ~Translation();
        void transform();
};


#endif
