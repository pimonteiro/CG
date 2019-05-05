#ifndef __POINT_LIGHT_H__
#define __POINT_LIGHT_H__

#include "light.h"

class PointLight : public Light {
    public:
        PointLight();
        ~PointLight();
        void draw();
};
#endif
