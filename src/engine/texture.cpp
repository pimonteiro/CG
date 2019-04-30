#include "headers/texture.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <IL/il.h>
#include <string>
#include <string.h>

Texture::Texture(){
    this->filename = NULL;
	this->imageHeight = -1;
	this->imageWidth = -1;
}

Texture::~Texture(){}

void Texture::addFile(std::string file){
	this->filename = new char[file.length() + 1];
	strcpy(this->filename, file.c_str());
}

void Texture::prepare(GLint buff){
	if(this->filename != NULL){
		unsigned int t, tw, th;
		unsigned char *texData;
		
		ilInit();
		ilGenImages(1, &t);
		ilBindImage(t);
		ilLoadImage((ILstring)this->filename);
		tw = ilGetInteger(IL_IMAGE_WIDTH);
		this->imageWidth = tw;
		th = ilGetInteger(IL_IMAGE_HEIGHT);
		this->imageHeight = th;
		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		texData = ilGetData();

		glGenTextures(1, &this->textBuffer);

		glBindTexture(GL_TEXTURE_2D, this->textBuffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);

		for (int i = 1; i < tw - 2; i++) {
			for (int j = 1; j < th - 1; j++) {
				this->pointArray.push_back(i+1);
				this->pointArray.push_back(j);
				this->pointArray.push_back(i);
				this->pointArray.push_back(j);
			}
		}

		glBindBuffer(GL_ARRAY_BUFFER, buff);
		glBufferData(GL_ARRAY_BUFFER, this->pointArray.size() * sizeof(float), &(this->pointArray[0]), GL_STATIC_DRAW);
	}
}

void Texture::draw(GLint buff){
	// TODO IMPROVE
	if(this->filename != NULL){
		glBindBuffer(GL_ARRAY_BUFFER, buff);
		for (int i = 1; i < this->imageWidth - 2; i++) {
			glDrawArrays(GL_TRIANGLE_STRIP, (this->imageWidth - 2) * 2 * i, (this->imageWidth - 2) * 2);
		}
	}
}