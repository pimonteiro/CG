#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "headers/model.h"

Model::Model(int numberPoints) {
        this->size = numberPoints * 3; /* each point has 3 floats */
        this->index = 0;
        this->pointArray = new float[this->size];
        this->texture = Texture();
        this->material = Material();
}

Model::~Model() {
        if (this->pointArray != nullptr)
                delete [] this->pointArray;
}

void Model::addElement(float cord) {
        this->pointArray[this->index++] = cord;
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
        float* v = new float[this->size];
        for(int i = 0; i < this->size; i++){
                v[i] = this->pointArray[i];
        }
        glBufferData(GL_ARRAY_BUFFER, this->size * sizeof(float), v, GL_STATIC_DRAW);

        this->texture.prepare(this->buffer[1]);
}

void Model::draw() {
        // Vertex Buffer
        this->material.setup();

        glBindBuffer(GL_ARRAY_BUFFER, this->buffer[0]);
        glVertexPointer(3,GL_FLOAT,0,0);
        glDrawArrays(GL_TRIANGLES, 0, this->size / 3);
        
        this->texture.draw(this->buffer[1]);
}

