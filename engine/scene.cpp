#include "scene.h"
#include "model.h"
#include <vector>


Scene::Scene() {
}

void Scene::addModel(Model* model) {
    modelsV.push_back(model);
}

std::vector<Model*> Scene::scene() {
    return this->modelsV;
}

void Scene::draw() {
    std::vector <Model*>::iterator it;
    for(it = this->modelsV.begin(); it != this->modelsV.end(); it++) {
        (*it)->draw();
    }
}
