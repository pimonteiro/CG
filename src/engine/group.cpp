#include "headers/group.h"
#include "headers/model.h"
#include "headers/transformation.h"

Group::Group() {
}

void Group::addTranformation(Transformation* t, int row) {
    transforms.at(row).push_back(t);
}

void Group::addModel(Model* m, int position) {
    models.at(position).push_back(m);
}

void Group::addMatrixElement(int row, int value) {
    matrix.at(row).push_back(value);
}

Transformation* Group::getTransformation(int row, int position) {
    return transforms.at(row).at(position);
}

Model* Group::getModel(int row, int position) {
    return models.at(row).at(position);
}

int Group::getDependency(int row, int column) {
    return matrix.at(row).at(column);
}

void Group::addMatrixRow(std::vector<int> fullRow) {
    matrix.push_back(fullRow);
}
