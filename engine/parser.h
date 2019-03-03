#ifndef __PARSER_H__
#define __PARSER_H__


#include "scene.h"
#include "model.h"
#include "tinyxml2.h"


using namespace tinyxml2;

class Parser {
  public:
    Parser();
    void ReadXML(Scene*, char*);
};
#endif
