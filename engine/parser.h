#ifndef __PARSER_H__
#define __PARSER_H__

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); }
#endif

#include "scene.h"
#include "model.h"
#include "tinyxml2.h"


using namespace tinyxml2;

class Parser{
    public:
        Parser();
        void ReadXML(Scene*, char*);
};
#endif
