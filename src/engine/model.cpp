#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "headers/model.h"

Model::Model(int n) {
        this->nPoints = n;
}

Model::~Model() {}

void Model::addVertexPoint(Point *p) {
       this->vertPoints.push_back(p);
}

void Model::addNormPoint(Point *p) {
       this->normPoints.push_back(p);
}

void Model::addTextPoint(Point *p) {
       this->textPoints.push_back(p);
}

void Model::prepare(){
        glGenBuffers(2, this->buffer);

        glBindBuffer(GL_ARRAY_BUFFER, this->buffer[0]);
        int n = this->nPoints * 3; // 3 coords x y z
        float* v = new float[n];
        int i = 0;
        for(auto &p : this->vertPoints){
                v[i++] = p->X();
                v[i++] = p->Y();
                v[i++] = p->Z();
        }
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * n, v, GL_STATIC_DRAW);


        glBindBuffer(GL_ARRAY_BUFFER, this->buffer[1]);
        v = new float[n];
        i = 0;
        for(auto &p : this->normPoints){
            v[i++] = p->X();
            v[i++] = p->Y();
            v[i++] = p->Z();
        }
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * n, v, GL_STATIC_DRAW);
}

void Model::draw() {
        // Vertex Buffer
        glBindBuffer(GL_ARRAY_BUFFER, this->buffer[0]);
        glVertexPointer(3,GL_FLOAT,0,0);

        // Normal Buffer
        glBindBuffer(GL_ARRAY_BUFFER, this->buffer[2]);
        glNormalPointer(GL_FLOAT, 0, 0);

        glDrawArrays(GL_TRIANGLES, 0, this->nPoints * 3);
}
