#include "headers/outputAux.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string writePoint(double a, double b, double c) {
    std::ostringstream os;
    os << a << " " << b << " " << c << '\n';
    return os.str();
}

void dumpFile(int nPoints, const std::ostringstream& os, const std::string& file) {

    std::ofstream outfile;

    outfile.open(file);
    if(!outfile.is_open()) {
        perror("ofstream.open");
    }

    outfile << std::to_string(nPoints) + "\n" + os.str();
    outfile.close();
}