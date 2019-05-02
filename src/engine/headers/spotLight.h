#ifndef __SPOT_LIGHT_H__
#define __SPOT_LIGHT_H__

#include "light.h"

class SpotLight : public Light {
    private:
        float spotDir[3];
        float cutOff;
        float exp;
    public:
        SpotLight(Point);
        ~SpotLight();
        void setSpotDir(float[3]);
        void setCutOff(float);
        void setExp(float);
        void draw();
};

#endif
