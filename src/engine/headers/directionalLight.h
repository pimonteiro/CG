#ifndef __DIRECTION_LIGHT_H__
#define __DIRECTION_LIGHT_H__

#include "light.h"

class DirectionalLight : public Light {
    public:
        DirectionalLight();
        ~DirectionalLight();
        void draw();
};
#endif
