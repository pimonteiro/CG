#ifndef __TRANSLATION_H__
#define __TRANSLATION_H__

#include "transformation.h"

class Translation: public Transformation {
public:
	Translation(Point p);
	void transform();
};


#endif