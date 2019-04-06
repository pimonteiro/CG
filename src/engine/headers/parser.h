#ifndef __PARSER_H__
#define __PARSER_H__


#include "group.h"

class Parser
{
        public:
                Parser();
                void ReadXML(Group*, const char*);
};
#endif
