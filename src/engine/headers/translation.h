#ifndef __TRANSLATION_H__
#define __TRANSLATION_H__
#include <vector>
#include "transformation.h"

class Translation: public Transformation
{
        public:
                Translation(Point);
                ~Translation();
                void transform();
};
#endif
