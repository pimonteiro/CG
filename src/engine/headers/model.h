#ifndef __MODEL_H__
#define __MODEL_H__

#include <string>
#include <vector>
#include "triangle.h"

class Model {
    private:
        std::vector<Triangle*> triV;
    public:
        Model();
        void addElement(Triangle*);
        void draw();
};

#endif
