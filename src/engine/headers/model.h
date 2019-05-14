#ifndef __MODEL_H__
#define __MODEL_H__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "../../lib/headers/point.h"
#include "material.h"
#include <vector>

class Model {
    private:
        int nPoints;
        std::vector<Point *> vertPoints;
        std::vector<Point *> normPoints;
        std::vector<Point *> textPoints;
        Material material;
    public:
        GLuint buffer[2];
        Model(int);
        ~Model();
        void addVertexPoint(Point *);
        void addNormPoint(Point *);
        void addTextPoint(Point *);
        void addMaterial(Material);
        void draw();
        void prepare();
};

#endif
