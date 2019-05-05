#include "headers/outputAux.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string writePoint(float a, float b, float c) {
        std::ostringstream os;
        os << a << " " << b << " " << c << '\n';
        return os.str();
}

std::string writeVector(std::vector<Point *> points) {
        std::ostringstream os;

        for (auto &p : points)
                os << writePoint(p->X(), p->Y(), p->Z());

        return os.str();
}

void dumpFile(const std::ostringstream &os, const std::string &file) {
        std::ofstream outfile;
        outfile.open(file);

        if (!outfile.is_open())
                perror("ofstream.open");

        outfile << os.str();
        outfile.close();
}
