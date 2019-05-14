#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "../../lib/headers/point.h"

class Light {
    private:
        Point pos;
        int state;
        int i;
        float color[4];
        float amb[4];
    public:
        Light();
        ~Light();
        virtual void draw() = 0;
        void setColor(float *);
        void setAmb(float *);
        void setIndex(int);
        void setPos(float *);
        int getState();
        void turnOn();
        void turnOff();
        int getState();
        Point POS() {
                return pos;
        }
        float *COLOR() {
                return color;
        }
        int INDEX() {
                return i;
        }
        float *AMB() {
                return amb;
        }
};

#endif
