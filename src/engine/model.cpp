#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "headers/model.h"

Model::Model(int n) {
        this->nPoints = n;
        this->texture = Texture();
        this->material = Material();
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

void Model::addTexture(Texture t){
        this->texture = t;
}

void Model::addMaterial(Material m){
        this->material = m;
}

void Model::prepare(){
        glGenBuffers(3, this->buffer);

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

        this->texture.prepare();

        glBindBuffer(GL_ARRAY_BUFFER, this->buffer[2]);
        v = new float[n];
        i = 0;
        for(auto &p : this->textPoints){
            v[i++] = p->X();
            v[i++] = p->Y();
            v[i++] = p->Z();
        }
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * n, v, GL_STATIC_DRAW);
}

void Model::draw() {

        this->material.setup();

        // Vertex Buffer
        glBindBuffer(GL_ARRAY_BUFFER, this->buffer[0]);
        glVertexPointer(3,GL_FLOAT,0,0);

        // Texture Buffer TODO verificar se dá erro quando não há imagem E se nao tem de ter cor na mesma ???
        glBindTexture(GL_TEXTURE_2D, this->textBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, buff);
        glTexCoordPointer(2, GL_FLOAT, 0, 0);
        glBindTexture(GL_TEXTURE_2D, 0);

        // Normal Buffer
        glBindBuffer(GL_ARRAY_BUFFER, this->buffer[2]);
        glNormalPointer(GL_FLOAT, 0, 0);

        glDrawArrays(GL_TRIANGLES, 0, this->points.size() * 3);
}
