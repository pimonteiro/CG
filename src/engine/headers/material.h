#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#define DIFFUSE     0
#define SPECULAR    1
#define EMISSIVE    2
#define AMBIENTE    3
#define NOSURFACE   -1

class Material {
    private:
        int type;
        float r, g, b;
    public:
        Material();
        ~Material();
        void addType(int);
        void addColor(float, float, float);
        void setup();
};

#endif
