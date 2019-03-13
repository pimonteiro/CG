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

void Group::teste(int nest) {
    std::cout << nest << " Numero de modelos: " << modelV.size() << std::endl;
    std::cout << nest << " Numero de transformations: " << transformV.size() << std::endl;

    std::vector <Group*>::iterator gIt;
    for(gIt = this->subGroupV.begin(); gIt != this->subGroupV.end(); gIt++){
        (*gIt)->teste(++nest);
    }
}

void Group::draw() {
    std::vector <Transformation*>::iterator tIt;
    for(tIt = this->transformV.begin(); tIt != this->transformV.end(); tIt++) {
        (*tIt)->transform();
    }

    std::vector <Model*>::iterator mIt;
    for(mIt = this->modelV.begin(); mIt != this->modelV.end(); mIt++) {
        (*mIt)->draw();
    }

    std::vector <Group*>::iterator gIt;
    for(gIt = this->subGroupV.begin(); gIt != this->subGroupV.end(); gIt++) {
        glPushMatrix();
        (*gIt)->draw();
        glPopMatrix();
    }
}
