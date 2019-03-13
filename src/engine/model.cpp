#include "headers/model.h"
#include "headers/triangle.h"
#include <iostream>
#include <random>


Model::Model() {
}

void Model::addElement(Triangle* triangle) {
    triV.push_back(triangle);
}

void Model::draw() {
    std::vector <Triangle*>::iterator itT;
    for(itT = this->triV.begin(); itT != this->triV.end(); itT++) {
        (*itT)->draw();
    }
}
