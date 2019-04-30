#ifndef __GROUP_H__
#define __GROUP_H__

#include <string>
#include <vector>
#include "transformation.h"
#include "model.h"
#include "light.h"


class Group {
    private:
        std::vector<Transformation *> transformV;
        std::vector<Model *> modelV;
        std::vector<Group *> subGroupV;
        std::vector<Light *> lights;
    public:
        Group();
        ~Group();
        void addTransformation(Transformation *t);
        void addModel(Model *m);
        void addGroup(Group *g);
        void addLights(std::vector<Light *>);
        void draw();
};
#endif
