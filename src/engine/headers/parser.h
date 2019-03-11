#ifndef __PARSER_H__
#define __PARSER_H__


#include "scene.h"

class Parser {
  public:
    Parser();
    void ReadXML(Scene*, const char*);
};
#endif
