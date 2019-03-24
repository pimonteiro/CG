#include <sstream>
#include "headers/annulus.h"
#include "headers/outputAux.h"
#include <cmath>


std::string annulus(float innerRadius, float outerRadius, float height, int div){
    std::ostringstream os;

    float angle = 2*M_PI / div;

    for(int i {0}; i < div; i++){
        float h = height/2;
        float alpha = angle * i;

        // Top Face
        os << writePoint(cos(alpha)*innerRadius,h,sin(alpha)*innerRadius);
        os << writePoint(cos(angle*(i+1))*innerRadius,h,sin(angle*(i+1))*innerRadius);
        os << writePoint(cos(alpha)*outerRadius,h,sin(alpha)*outerRadius);
        os << writePoint(cos(alpha)*outerRadius,h,sin(alpha)*outerRadius);
        os << writePoint(cos(angle*(i+1))*innerRadius,h,sin(angle*(i+1))*innerRadius);
        os << writePoint(cos(angle*(i+1))*outerRadius,h,sin(angle*(i+1))*outerRadius);

        // Bottom Face
        os << writePoint(cos(alpha)*innerRadius,-h,sin(alpha)*innerRadius);
        os << writePoint(cos(alpha)*outerRadius,-h,sin(alpha)*outerRadius);
        os << writePoint(cos(angle*(i+1))*innerRadius,-h,sin(angle*(i+1))*innerRadius);
        os << writePoint(cos(alpha)*outerRadius,-h,sin(alpha)*outerRadius);
        os << writePoint(cos(angle*(i+1))*outerRadius,-h,sin(angle*(i+1))*outerRadius);
        os << writePoint(cos(angle*(i+1))*innerRadius,-h,sin(angle*(i+1))*innerRadius);

        // Sides
        os << writePoint(cos(alpha)*outerRadius,h,sin(alpha)*outerRadius);
        os << writePoint(cos(angle*(i+1))*outerRadius,h,sin(angle*(i+1))*outerRadius);
        os << writePoint(cos(alpha)*outerRadius,-h,sin(alpha)*outerRadius);
        os << writePoint(cos(angle*(i+1))*outerRadius,-h,sin(angle*(i+1))*outerRadius);
        os << writePoint(cos(alpha)*outerRadius,-h,sin(alpha)*outerRadius);
        os << writePoint(cos(angle*(i+1))*outerRadius,h,sin(angle*(i+1))*outerRadius);
    }
    return os.str();
}