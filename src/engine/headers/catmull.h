#ifndef __CATMULL_H__
#define __CATMULL_H__

#include <vector>
#include "transformation.h"
#include "../../lib/headers/point.h"

class Catmull: public Transformation {
    private:
        std::vector<Point *> contP;
        int ownRotation;
        float time;
        float t;            // Parametric value of where the object is in the curve.
        float yAxis[3];

    public:
        Catmull();
        ~Catmull();
        void addFlag(int);
        void addTime(int);
        void setYAxis(float *);
        void incT();
        int getRotation();
        void addPoint(Point *);
        Point getCatmullRomPoint(float, Point, Point, Point, Point, float *);
        Point getGlobalCatmullRomPoint(float, float *);
        void renderCatmullRomCurve();
        void transform();
};
#endif