#ifndef __GROUP_H__
#define __GROUP_H__

#include <string>
#include <vector>
#include "transformation.h"
#include "model.h"


class Group {
  private:
    std::vector<Transformation*> transforms;
    std::vector<std::vector<Model*>> models;
    std::vector<std::vector<int>> matrix;
  public:
    Group();
    void addTranformation(Transformation* t);
    void addModel(Model* m, int position);
    void addMatrixElement(int row, int value);
    Transformation* getTransformation(int position);
    Model* getModel(int row, int position);
    int getDependency(int row, int column);
    void addMatrixRow(std::vector<int> fullRow);
};
#endif
