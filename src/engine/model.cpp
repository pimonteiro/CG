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

void Model::addPoint(Point *p) {
       this->points.push_back(p);
}

void Model::addTexture(Texture t){
        this->texture = t;
}

void Model::addMaterial(Material m){
        this->material = m;
}

void Model::prepare(){
        glGenBuffers(2, this->buffer);
        glBindBuffer(GL_ARRAY_BUFFER, this->buffer[0]);

        int n = this->points.size() * 3; // 3 coords x y z
        float* v = new float[n];
        int i = 0;
        for(auto &p : this->points){
                v[i++] = p->X();
                v[i++] = p->Y();
                v[i++] = p->Z();
        }
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * n, v, GL_STATIC_DRAW);

        //this->texture.prepare(this->buffer[1]);
}

void Model::draw() {

        this->material.setup();

        // Vertex Buffer
        //glColor3f(1.0f,1.0f,1.0f);
        glBindBuffer(GL_ARRAY_BUFFER, this->buffer[0]);
        glVertexPointer(3,GL_FLOAT,0,0);
        glDrawArrays(GL_TRIANGLES, 0, this->points.size() * 3);

        //this->texture.draw(this->buffer[1]);
}
