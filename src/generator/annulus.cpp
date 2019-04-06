#include <sstream>
#include "headers/annulus.h"
#include "headers/outputAux.h"
#include <cmath>


std::string
annulus(float innerRadius, float outerRadius, float height, int div)
{
        std::ostringstream os;
        std::ostringstream r;
        float angle {static_cast<float>(2 * M_PI / div) };
        float h { height / 2 };
        int points {0};

        for (int i {0}; i < div; i++) {
                float alpha { static_cast<float>(angle * i) };
                os << writePoint(cos(alpha)*innerRadius, h, sin(alpha)*innerRadius);
                os << writePoint(cos(angle * (i + 1))*innerRadius, h, sin(angle * (i + 1))*innerRadius);
                os << writePoint(cos(alpha)*outerRadius, h, sin(alpha)*outerRadius);
                os << writePoint(cos(alpha)*outerRadius, h, sin(alpha)*outerRadius);
                os << writePoint(cos(angle * (i + 1))*innerRadius, h, sin(angle * (i + 1))*innerRadius);
                os << writePoint(cos(angle * (i + 1))*outerRadius, h, sin(angle * (i + 1))*outerRadius);
                os << writePoint(cos(alpha)*innerRadius, -h, sin(alpha)*innerRadius);
                os << writePoint(cos(alpha)*outerRadius, -h, sin(alpha)*outerRadius);
                os << writePoint(cos(angle * (i + 1))*innerRadius, -h, sin(angle * (i + 1))*innerRadius);
                os << writePoint(cos(alpha)*outerRadius, -h, sin(alpha)*outerRadius);
                os << writePoint(cos(angle * (i + 1))*outerRadius, -h, sin(angle * (i + 1))*outerRadius);
                os << writePoint(cos(angle * (i + 1))*innerRadius, -h, sin(angle * (i + 1))*innerRadius);
                os << writePoint(cos(alpha)*innerRadius, h, sin(alpha)*innerRadius);
                os << writePoint(cos(alpha)*innerRadius, -h, sin(alpha)*innerRadius);
                os << writePoint(cos(angle * (i + 1))*innerRadius, h, sin(angle * (i + 1))*innerRadius);
                os << writePoint(cos(angle * (i + 1))*innerRadius, -h, sin(angle * (i + 1))*innerRadius);
                os << writePoint(cos(angle * (i + 1))*innerRadius, h, sin(angle * (i + 1))*innerRadius);
                os << writePoint(cos(alpha)*innerRadius, -h, sin(alpha)*innerRadius);
                os << writePoint(cos(alpha)*outerRadius, h, sin(alpha)*outerRadius);
                os << writePoint(cos(angle * (i + 1))*outerRadius, h, sin(angle * (i + 1))*outerRadius);
                os << writePoint(cos(alpha)*outerRadius, -h, sin(alpha)*outerRadius);
                os << writePoint(cos(angle * (i + 1))*outerRadius, -h, sin(angle * (i + 1))*outerRadius);
                os << writePoint(cos(alpha)*outerRadius, -h, sin(alpha)*outerRadius);
                os << writePoint(cos(angle * (i + 1))*outerRadius, h, sin(angle * (i + 1))*outerRadius);
                points += 24;
        }

        r << points << "\n" << os.str();
        return r.str();
}