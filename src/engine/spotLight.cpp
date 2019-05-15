#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "headers/spotLight.h"

SpotLight::SpotLight(): Light() {
        float defSpotDir[3] {0, 0, -1};

        for (int i {0}; i < 3; i++)
                this->spotDir[i] = defSpotDir[i];

        this->cutOff = 45; // Default Values

        this->exp = 0;      // Default Values
}

SpotLight::~SpotLight() {}

void SpotLight::setSpotDir(float d[3]) {
        for (int i {0}; i < 3; i++)
                this->spotDir[i] = d[i];
}

void SpotLight::setCutOff(float c) {
        this->cutOff = c;
}

void SpotLight::setExp(float ex) {
        this->exp = ex;
}

void SpotLight::draw() {
        Point p {this->POS()};
        float pos[4] {
                p.X(), p.Y(), p.Z(), 1.0f
        };
        glLightfv(GL_LIGHT0 + this->INDEX(), GL_POSITION, pos);
        glLightfv(GL_LIGHT0 + this->INDEX(), GL_DIFFUSE, this->COLOR());
        glLightfv(GL_LIGHT0 + this->INDEX(), GL_SPOT_DIRECTION, this->spotDir);
        glLightf(GL_LIGHT0 + this->INDEX(), GL_SPOT_CUTOFF, this->cutOff);
        glLightf(GL_LIGHT0 + this->INDEX(), GL_SPOT_EXPONENT, this->exp);
}
