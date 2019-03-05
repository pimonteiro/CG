#ifndef __SCENE_H__
#define __SCENE_H__

#include <string>
#include "model.h"
#include <vector>

class  Scene {
    std::vector<Model*> modelsV;
  public:
    Scene();
    void addModel(Model*);
    std::vector<Model*> scene();
    void draw();
};
#endif
