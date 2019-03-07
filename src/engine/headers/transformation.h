#ifndef __TRANSFORMATION_H__
#define __TRANSFORMATION_H__

#include "point.h"

class Transformation {
public:
	Transformation(Point);
	virtual void transform() = 0;
	Point V(){
		return v;
	}

private:
	Point v;
};

#endif