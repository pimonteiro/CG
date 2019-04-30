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

class Model {
    private:
        float r, g, b;
        int size; /* number of dots */
        int index;
        float *pointArray;
        Texture texture;
        Material material;
    public:
        GLuint buffer[2];
        Model(int);
        ~Model();
        void addTexture(Texture);
        void addMaterial(Material);
        void addElement(float);
        void draw();
        void prepare();
};

#endif
