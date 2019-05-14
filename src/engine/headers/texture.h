#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <vector>
#include <string>
#include "../../lib/headers/point.h"
#include "material.h"

class Texture {
    private:
        char *filename;
        unsigned int imageWidth;
        unsigned int imageHeight;
        Material *material;
    public:
        unsigned int textBuffer;
        Texture();
        ~Texture();
        void addFile(std::string);
        void addMaterial(Material *);
        void setup();
        void loadImage();
};

#endif
