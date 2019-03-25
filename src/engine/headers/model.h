#ifndef __MODEL_H__
#define __MODEL_H__

#include <string>
#include <vector>
#include "triangle.h"

class Model {
    private:
        std::vector<Triangle*> triV;
        float r, g, b;
    public:
        Model();
        ~Model();
        void addElement(Triangle*);
        void draw();
        void drawC();
        void addColour(float, float, float);
};

#endif
