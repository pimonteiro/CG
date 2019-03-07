#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "headers/rotation.h"


Rotation::Rotation(Point p, float ang): Transformation(p), angle(ang) {}

void Rotation::transform(){
	Point v = V();
	glRotatef(angle,v.X(),v.Y(),v.Z());
}