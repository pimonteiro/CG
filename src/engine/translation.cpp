#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "headers/translation.h"


Translation::Translation(Point p): Transformation(p) {}

void Translation::transform(){
	Point v { V() };
	glTranslatef(v.X(),v.Y(),v.Z());
}