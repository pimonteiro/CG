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
        void addTransformation(Transformation *);
        void addModel(Model *);
        void addGroup(Group *);
        void addLight(Light *);
        Light *getLight(int );
        void prepare();
        void draw();
};
#endif
