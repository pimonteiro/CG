#include <iostream>

#include <fstream>
using namespace std;

void plane(float size){
  ofstream myfile;
  myfile.open("plane.3D");
  myfile << "6\n";
  myfile << size/2 << " 0 " << size/2 << "\n"; //A
  myfile << size/2 << " 0 " << -size/2 << "\n"; //B
  myfile << - size/2 << " 0 " << size/2 << "\n"; //D
  myfile << size/2 << " 0 " << -size/2 << "\n"; //B
  myfile <<  -size/2 << " 0 " << -size/2 << "\n"; //C
  myfile << - size/2 << " 0 " << size/2 << "\n"; //D
  myfile.close(); 
}
