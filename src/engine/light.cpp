#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "headers/light.h"
#include "../lib/headers/point.h"


Light::Light() {
        this->i = -1;
        this->state = 0;
        float defPos[4] {0, 0, 1, 0};
        float defColor[4] {1, 1, 1, 1};
        float defAmb[4] {0.2, 0.2, 0.2, 1};

        for (int i = 0; i < 4; i++) {
                this->color[i] = defColor[i];
                this->amb[i] = defAmb[i];
        }

        this->pos = Point(defPos[0], defPos[1], defPos[2]);
}

Light::~Light() {}

void Light::setColor(float c[4]) {
        for (int i {0}; i < 4; i++)
                this->color[i] = c[i];
}

void Light::setAmb(float c[4]) {
        for (int i {0}; i < 4; i++)
                this->amb[i] = c[i];
}

void Light::setPos(float c[3]) {
        this->pos = Point(c[0], c[1], c[2]);
}

void Light::setIndex(int i) {
        this->i = i;
}

int Light::getState(){
        return this->state;
}

void Light::turnOn() {
        glEnable(GL_LIGHT0 + this->i);
        this->state = 1;
}

void Light::turnOff() {
        glDisable(GL_LIGHT0 + this->i);
        this->state = 0;
}
