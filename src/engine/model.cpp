#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "headers/model.h"

Model::Model(int n) {
        this->nPoints = n;
        this->texture = new Texture();
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

void Model::addTexture(Texture *t) {
        this->texture = t;
}

void Model::prepare() {
        glGenTextures(1, &this->texture->textBuffer);        //TODO MUDAR DE SITIO?
        this->texture->loadImage();
        glGenBuffers(3, this->buffer);
        glBindBuffer(GL_ARRAY_BUFFER, this->buffer[0]);
        int n {this->nPoints * 3}; // 3 coords x y z
        float *v { new float[n]};
        int i {0};

        for (auto &p : this->vertPoints) {
                v[i++] = p->X();
                v[i++] = p->Y();
                v[i++] = p->Z();
        }

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * n, v, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, this->buffer[1]);
        v = new float[n];
        i = 0;

        for (auto &p : this->normPoints) {
                v[i++] = p->X();
                v[i++] = p->Y();
                v[i++] = p->Z();
        }

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * n, v, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, this->buffer[2]);
        v = new float[n];
        i = 0;

        for (auto &p : this->textPoints) {
                v[i++] = p->X();
                v[i++] = p->Y();
        }

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->textPoints.size() * 2, v, GL_STATIC_DRAW);
}

void Model::draw() {
        this->texture->setup();
        glBindTexture(GL_TEXTURE_2D, this->texture->textBuffer);
        
        // Vertex Buffer
        glBindBuffer(GL_ARRAY_BUFFER, this->buffer[0]);
        glVertexPointer(3, GL_FLOAT, 0, 0);
        // Normal Buffer
        glBindBuffer(GL_ARRAY_BUFFER, this->buffer[1]);
        glNormalPointer(GL_FLOAT, 0, 0);
        // Text Buffer
        glBindBuffer(GL_ARRAY_BUFFER, this->buffer[2]);
        glTexCoordPointer(2, GL_FLOAT, 0, 0);
        glDrawArrays(GL_TRIANGLES, 0, this->nPoints * 3);
        
        glBindTexture(GL_TEXTURE_2D, 0);
}
