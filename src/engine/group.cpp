#include "headers/group.h"
#include "headers/model.h"
#include "headers/transformation.h"
#include "headers/rotation.h"
#include "headers/scale.h"
#include "headers/translation.h"
#include <vector>


#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

Group::Group() {
}

void Group::addTransformation(Transformation* t){
    transformV.push_back(t);
}

void Group::addModel(Model* m){
    modelV.push_back(m);
}

void Group::addGroup(Group* g){
    subGroupV.push_back(g);
}

void Group::draw() {
    for (auto& t : this->transformV) {
        t->transform();
    }
    for (auto& m : this->modelV) {
        m->draw();
    }
    for (auto& g : this->subGroupV) {
        glPushMatrix();
        g->draw();
        glPopMatrix();
    }
}
