#include <sstream>
#include "headers/plane.h"

std::string plane(float size) {
    std::ostringstream os;

    os << "6\n";
    os <<  size/2 << " 0 " <<  size/2 << "\n"; //A
    os <<  size/2 << " 0 " << -size/2 << "\n"; //B
    os << -size/2 << " 0 " <<  size/2 << "\n"; //D
    os <<  size/2 << " 0 " << -size/2 << "\n"; //B
    os << -size/2 << " 0 " << -size/2 << "\n"; //C
    os << -size/2 << " 0 " <<  size/2 << "\n"; //D

   return os.str();
}
