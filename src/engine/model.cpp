#include "headers/model.h"
#include "headers/triangle.h"
#include <iostream>
#include <random>


Model::Model() {
}

void Model::addElement(Triangle *triangle) {
    triV.push_back(triangle);
}

void Model::draw() {
    for (auto& t : this->triV) {
        t->draw();
    }
}
