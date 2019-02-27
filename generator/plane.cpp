#include <iostream>
#include <fstream>

void plane(float size, const std::string &file) {
    std :: ofstream myfile;
    myfile.open(file);

    myfile << "6\n";
    myfile <<  size/2 << " 0 " <<  size/2 << "\n"; //A
    myfile <<  size/2 << " 0 " << -size/2 << "\n"; //B
    myfile << -size/2 << " 0 " <<  size/2 << "\n"; //D
    myfile <<  size/2 << " 0 " << -size/2 << "\n"; //B
    myfile << -size/2 << " 0 " << -size/2 << "\n"; //C
    myfile << -size/2 << " 0 " <<  size/2 << "\n"; //D

    myfile.close();
}
