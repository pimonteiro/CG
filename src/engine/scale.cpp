#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "headers/scale.h"


Scale::Scale(Point p): Transformation(p) {}

void Scale::transform(){
	Point v { V() };
	glScalef(v.X(),v.Y(),v.Z());
}