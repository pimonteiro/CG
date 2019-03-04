#include <cstdio>
#include <sstream>
#include <iostream>
#include "headers/box.h"

std::string planeXoZ(float,float,float,int,int);
std::string planeXoY(float,float,float,int,int);
std::string planeZoY(float,float,float,int,int);

std::string box(float x, float y, float z, int div) {
    std::ostringstream f;

    int n_v = x+y+z; //TEMP solution for total number of vertex
    f << n_v << "\n";

    f << planeXoZ(x,y,z,div,1);
    f << planeXoZ(x,y,z,div,0);
    f << planeXoY(x,y,z,div,1);
    f << planeXoY(x,y,z,div,0);
    f << planeZoY(x,y,z,div,1);
    f << planeZoY(x,y,z,div,0);

    return f.str();
}

std::string planeXoZ(float x, float y, float z, int div, int side_view) {
    std::ostringstream f;
    float shift {x/div};

    float n_x {x/2};
    float n_z {z/2};

    float alt {y/2};

    if(side_view == 1) // Top side visible
        for(int i {0}; i < div; i++) {
            for(int j {0}; j < div; j++) {
                f << n_x << " " << alt << " " << n_z << "\n";
                f << n_x - shift << " " << alt << " " << n_z - shift << "\n";
                f << n_x - shift << " " << alt << " " << n_z << "\n";
                f << n_x - shift << " " << alt << " " << n_z - shift << "\n";
                f << n_x << " " << alt << " " << n_z << "\n";
                f << n_x << " " << alt << " " << n_z - shift << "\n";

                n_z -= shift;
            }
            n_x -= shift;
            n_z = z/2;
        } else { // Under side visible
            for(int i {0}; i < div; i++) {
                for(int j {0}; j < div; j++) {
                    f << n_x << " " << -alt << " " << n_z << "\n";
                    f << n_x - shift << " " << -alt << " " << n_z << "\n";
                    f << n_x - shift << " " << -alt << " " << n_z - shift << "\n";
                    f << n_x - shift << " " << -alt << " " << n_z - shift << "\n";
                    f << n_x << " " << -alt << " " << n_z - shift << "\n";
                    f << n_x << " " << -alt << " " << n_z << "\n";

                    n_z -= shift;
                }
                n_x -= shift;
                n_z = z/2;
            }
        }
    return f.str();
}

std::string planeXoY(float x, float y, float z, int div, int side_view) {
    std::ostringstream f;
    float shift {x/div};

    float n_x {x/2};
    float lado {z/2};

    float n_y {y/2};

    if(side_view == 1) // Front side visible
        for(int i {0}; i < div; i++) {
            for(int j {0}; j < div; j++) {
                f << n_x << " " << n_y << " " << lado << "\n";
                f << n_x - shift << " " << n_y << " " << lado << "\n";
                f << n_x << " " << n_y - shift << " " << lado << "\n";
                f << n_x - shift << " " << n_y << " " << lado << "\n";
                f << n_x - shift << " " << n_y - shift << " " << lado << "\n";
                f << n_x << " " << n_y - shift << " " << lado << "\n";

                n_y -= shift;
            }
            n_x -= shift;
            n_y = y/2;
        } else { // Back side visible
            for(int i {0}; i < div; i++) {
                for(int j {0}; j < div; j++) {
                    f << n_x << " " << n_y << " " << -lado << "\n";
                    f << n_x << " " << n_y - shift << " " << -lado << "\n";
                    f << n_x - shift << " " << n_y << " " << -lado << "\n";
                    f << n_x - shift << " " << n_y << " " << -lado << "\n";
                    f << n_x << " " << n_y - shift << " " << -lado << "\n";
                    f << n_x - shift << " " << n_y - shift << " " << -lado << "\n";

                    n_y -= shift;
                }
                n_x -= shift;
                n_y = y/2;
            }
        }
    return f.str();
}

std::string planeZoY(float x, float y, float z, int div, int side_view) {
    std::ostringstream f;
    float shift {x/div};

    float lado {x/2};
    float n_z {z/2};

    float n_y {y/2};

    if(side_view == 1) // Left side visible
        for(int i {0}; i < div; i++) {
            for(int j {0}; j < div; j++) {
                f << lado << " " << n_y << " " << n_z - shift << "\n";
                f << lado << " " << n_y << " " << n_z << "\n";
                f << lado << " " << n_y - shift << " " << n_z << "\n";
                f << lado << " " << n_y << " " << n_z - shift << "\n";
                f << lado << " " << n_y - shift << " " << n_z << "\n";
                f << lado << " " << n_y - shift << " " << n_z - shift << "\n";

                n_y -= shift;
            }
            n_z -= shift;
            n_y = y/2;
        } else { // Right side visible
            for(int i {0}; i < div; i++) {
                for(int j {0}; j < div; j++) {
                    f << lado << " " << n_y << " " << n_z - shift << "\n";
                    f << lado << " " << n_y - shift << " " << n_z << "\n";
                    f << lado << " " << n_y << " " << n_z << "\n";
                    f << lado << " " << n_y << " " << n_z - shift << "\n";
                    f << lado << " " << n_y - shift << " " << n_z - shift << "\n";
                    f << lado << " " << n_y - shift << " " << n_z << "\n";

                    n_y -= shift;
                }
                n_z -= shift;
                n_y = y/2;
            }
        }
    return f.str();
}