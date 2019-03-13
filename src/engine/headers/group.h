#ifndef __GROUP_H__
#define __GROUP_H__

#include <string>
#include <vector>
#include "transformation.h"
#include "model.h"


class Group {
    private:
        std::vector<Transformation*> transformV;
        std::vector<Model*> modelV;
        std::vector<Group*> subGroupV;
    public:
        Group();
        void addTransformation(Transformation* t);
        void addModel(Model* m);
        void addGroup(Group* g);
        void draw();
        void teste(int);
};
#endif
