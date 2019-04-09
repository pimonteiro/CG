#ifndef __MODEL_H__
#define __MODEL_H__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif


class Model
{
        private:
                float r, g, b;
                GLuint *buffer;
                int size; /* number of dots */
                int index;
                float *pointArray;
        public:
                Model(int);
                ~Model();
                void addElement(float);
                void draw();
                void addColour(float, float, float);
                void prepare();
};

#endif
