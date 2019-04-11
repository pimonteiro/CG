#ifndef __TRANSLATION_H__
#define __TRANSLATION_H__
#include <vector>
#include "transformation.h"

class Translation: public Transformation
{
        private:
                std::vector<Point*> pointV;
        public:
                Translation();
                void addPoint(Point*);
                ~Translation();
                void transform();
};


#endif
