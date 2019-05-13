#ifndef __MODEL_H__
#define __MODEL_H__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "texture.h"
#include "material.h"
#include "../../lib/headers/point.h"
#include <vector>

class Model {
    private:
        int nPoints;
        std::vector<Point *> vertPoints;
        std::vector<Point *> normPoints;
        std::vector<Point *> textPoints;
        Texture *texture;
    public:
        GLuint buffer[3];
        Model(int);
        ~Model();
        void addTexture(Texture *);
        void addVertexPoint(Point *);
        void addNormPoint(Point *);
        void addTextPoint(Point *);
        void draw();
        void prepare();
};

#endif
