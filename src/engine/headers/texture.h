#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <vector>
#include "../../lib/headers/point.h"

class Texture {
    private:
        char* filename;
        std::vector<float> pointArray;
        unsigned int imageWidth;
        unsigned int imageHeight;
    public:
        unsigned int textBuffer;
        Texture();
        ~Texture();
        void addFile(char*);
        void prepare(GLint);
        void draw(GLint);
};

#endif