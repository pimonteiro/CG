#include <sstream>
#include "headers/plane.h"
#include "headers/outputAux.h"

std::string plane(double xO, double yO, double zO, double xP, double zP, int type, int place) {
    std::ostringstream os;

    os << "6\n";

    double x, y, z;
    x = xP/2;
    y = 0;
    z = zP/2;
    double flag {1};

    if (type == 1) {
        y = -z;
        z = 0;
    }

    else if (type == 2) {
        y = x;
        x = 0;
        flag = -1;
    }

    if (place == 1) {
        // frente
        os << writePoint(-x+xO,y+yO, z+zO); // 1
        os << writePoint(x+xO,flag*y+yO, z+zO); // 2
        os << writePoint(x+xO,-y+yO, -z+zO); // 3

        os << writePoint(-x+xO,y+yO, z+zO); // 1
        os << writePoint(x+xO,-y+yO, -z+zO); // 3
        os << writePoint(-x+xO,-flag*y+yO, -z+zO); // 4
    }

    else if (place == 0) {
        // trás
        os << writePoint(x+xO,-y+yO, -z+zO); // 3
        os << writePoint(x+xO,flag*y+yO, z+zO); // 2
        os << writePoint(-x+xO,y+yO, z+zO); // 1

        os << writePoint(-x+xO,-flag*y+yO, -z+zO); // 4
        os << writePoint(x+xO,-y+yO, -z+zO); // 3
        os << writePoint(-x+xO,y+yO, z+zO); // 1
    }
    return os.str();
}
