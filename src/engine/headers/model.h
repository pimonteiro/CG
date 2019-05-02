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
        std::vector<Point *> points;
        Texture texture;
        Material material;
    public:
        GLuint buffer[2];
        Model(int);
        ~Model();
        void addTexture(Texture);
        void addMaterial(Material);
        void addPoint(Point *);
        void draw();
        void prepare();
};

#endif
