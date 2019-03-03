#include "point.h"
#include <sstream>
#include <string>

Point::Point(): x(0), y(0), z(0) {}

Point::Point(double x, double y, double z) : x(x), y(y), z(z) {}

std::string Point::toString() {
    std::ostringstream os;
    os << x << ' ' << y << ' ' << z << '\n';
    return os.str();
}
