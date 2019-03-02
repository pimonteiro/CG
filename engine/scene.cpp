#include "scene.h"

Scene::Scene() {
}

void Scene::addModel(Model* model) {
    model_vector.push_back(model);
}

vector<Model*> Scene::scene() {
    return this->model_vector;
}

void Scene::draw() {
    vector <Model*>::iterator it;

    for(it = this->model_vector.begin(); it != this->model_vector.end(); it++) {
        (*it)->draw();
    }
}
