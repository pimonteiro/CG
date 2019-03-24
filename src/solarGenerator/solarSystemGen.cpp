#include <sstream>
#include <iostream>
#include "../generator/headers/sphere.h"
#include "../generator/headers/outputAux.h"
#include "../generator/headers/annulus.h"
#include "../engine/headers/point.h"



#define SIZE    5
#define STARSTACKS  100
#define BIGSTACKS   50
#define SMALLSTACKS  10


#define DMERCURY    150
#define DSATTELITE  20

using namespace std;

//"mercury", "venus", "earth", "mars", "pluto", "jupiter", "saturn", "uranus", "neptune", "moon", "titan", "io", "europa", "callisto"
double plProp[14] {1.38, 1.95, 2.3, 1.53, 1.18, 11.60, 10.40, 5.04, 4.88, 0.7, 1.45, 0.95,0.6, 1.38};
double plD[14] {DMERCURY, 1.7*DMERCURY, 2.4*DMERCURY, 3*DMERCURY, 8.8*DMERCURY, 4.2*DMERCURY, 5.9*DMERCURY, 7*DMERCURY, 8*DMERCURY, DSATTELITE, 3.5*DSATTELITE, 3.5*DSATTELITE, 4.5*DSATTELITE, 5.4*DSATTELITE};
Point colors[14] {Point(0.36,0.36,0.36),Point(0.8,0.5,0.2),Point(0.31,0.65,0.76),Point(0.55,0.15,0),Point(0.93,0.85,0.68),Point(0.93,0.8,0.38),Point(0.93,0.86,0.51),
                  Point(0.61,0.77,0.89),Point(0.23,0.35,0.58),Point(0.84,0.84,0.84),Point(0.93,0.8,0.38),Point(0.93,0.85,0.51),Point(0.93,0.57,0.13),Point(0.27,0.27,0.27)};

float angle {40};
float angleMoons {60};


void genSmallSizePlanets(ostringstream* solar){
    ostringstream file;
    file << sphere(1.0f * SIZE, SMALLSTACKS, SMALLSTACKS);
    string pF {"smallPlanets.3d" };
    dumpFile(file, pF);

    for(int i { 0 }; i < 5; i++){
        *solar << "     <group>" << endl;
        float ang;
        if(i == 4) ang = angle*9;
        else ang = angle*i;
        *solar << "         <rotate angle=\"" << ang << "\" axisX=\"0\" axisY=\"1\" axisZ=\"0\" />" << endl;
        *solar << "         <translate x=\"" << plD[i] << "\" y=\"0\" z=\"0\"" << "/>" << endl;
        *solar << "         <scale x=\"" << plProp[i] << "\" y=\"" << plProp[i] << "\" z=\"" << plProp[i] << "\" />" << endl;
        *solar << "         <models>" << endl;
        *solar << "             <model file=\"" << pF << "\" r=\"" << colors[i].X() << "\" g=\"" << colors[i].Y() << "\" b=\"" << colors[i].Z() << "\" />" << endl;
        *solar << "         </models>" << endl;
        if(i == 2){
            double prp { (1.0f/plProp[i]) };
            *solar << "             <group>" << endl;
            *solar << "                 <scale x=\"" << prp << "\" y=\"" << prp << "\" z=\"" << prp << "\" />" << endl;
            *solar << "                 <rotate angle=\"" << angleMoons << "\" axisX=\"0\" axisY=\"1\" axisZ=\"0\" />" << endl;
            *solar << "                 <translate x=\"" << plD[9] << "\" y=\"0\" z=\"0\"" << "/>" << endl;
            *solar << "                 <scale x=\"" << plProp[9] << "\" y=\"" << plProp[9] << "\" z=\"" << plProp[9] << "\" />" << endl;
            *solar << "                 <models>" << endl;
            *solar << "                     <model file=\"" << pF << "\" r=\"" << colors[9].X() << "\" g=\"" << colors[9].Y() << "\" b=\"" << colors[9].Z() << "\" />" << endl;
            *solar << "                 </models>" << endl;
            *solar << "             </group>" << endl;
        }
        *solar << "     </group>" << endl;
    }
}

void genStars(ostringstream* solar){
    string s1 { "sun.3d" };
    float s1Prop { 24 };

    ostringstream file;
    file << sphere(1.0f * SIZE, STARSTACKS, STARSTACKS);
    dumpFile(file,s1);

    *solar << "     <group>" << endl;
    *solar << "         <scale x=\"" << s1Prop << "\" y=\"" << s1Prop << "\" z=\"" << s1Prop << "\" />" << endl;
    *solar << "         <models>" << endl;
    *solar << "             <model file=\"" << s1 <<  "\" r=\"1\" g=\"0.2\" b=\"0\" />" << endl;
    *solar << "         </models>" << endl;
    *solar << "     </group>" << endl;
}

void genBigSizePlanets(ostringstream* solar){
    ostringstream file;
    file << sphere(1.0f * SIZE, BIGSTACKS, BIGSTACKS);
    string pF { "bigPlanets.3d" };
    dumpFile(file, pF);

    for(int i { 5 }; i < 9; i++){
        *solar << "     <group>" << endl;
        *solar << "         <rotate angle=\"" << angle*i << "\" axisX=\"0\" axisY=\"1\" axisZ=\"0\" />" << endl;
        *solar << "         <translate x=\"" << plD[i] << "\" y=\"0\" z=\"0\"" << "/>" << endl;
        *solar << "         <scale x=\"" << plProp[i] << "\" y=\"" << plProp[i] << "\" z=\"" << plProp[i] << "\" />" << endl;
        *solar << "         <models>" << endl;
        *solar << "             <model file=\"" << pF << "\" r=\"" << colors[i].X() << "\" g=\"" << colors[i].Y() << "\" b=\"" << colors[i].Z() << "\" />" << endl;
        *solar << "         </models>" << endl;
        switch (i) {
            case 5:
                for(int j {0}; j < 3; j++){
                    float prp = (1.0f/plProp[i]);
                    *solar << "         <group>" << endl;
                    *solar << "             <scale x=\"" << prp << "\" y=\"" << prp << "\" z=\"" << prp << "\" />" << endl;
                    *solar << "             <rotate angle=\"" << angleMoons << "\" axisX=\"0\" axisY=\"1\" axisZ=\"0\" />" << endl;
                    *solar << "             <translate x=\"" << plD[11 + j] << "\" y=\"0\" z=\"0\" />" << endl;
                    *solar << "             <scale x=\"" << plProp[11+j] << "\" y=\"" << plProp[11+j] << "\" z=\"" << plProp[11+j] << "\" />" << endl;
                    *solar << "             <models>" << endl;
                    *solar << "                 <model file=\"smallPlanets.3d\" r=\"" << colors[11+j].X() << "\" g=\"" << colors[11+j].Y() << "\" b=\"" << colors[11+j].Z() << "\" />" << endl;
                    *solar << "             </models>" << endl;
                    *solar << "         </group>" << endl;
                    angleMoons += angleMoons;
                }
                break;
            case 6:
                ostringstream file1;
                ostringstream file2;
                ostringstream file3;

                file1 << annulus(9, 12, 0.4, 1000);
                file2 << annulus(12.5, 15.5, 0.4, 1000);
                file3 << annulus(16, 16.8, 0.4, 1000);
                dumpFile(file1, "saturnRing1.3d");
                dumpFile(file2, "saturnRing2.3d");
                dumpFile(file3, "saturnRing3.3d");

                float prp = (1.0f/plProp[i]);
                *solar << "         <group>" << endl;
                *solar << "             <rotate angle=\"15\" axisX=\"1\" axisY=\"0\" axisZ=\"0\" />" << endl;
                *solar << "             <models>" << endl;
                *solar << "                 <model file=\"saturnRing1.3d\" r=\"0\" g=\"0\" b=\"0.8\" />" << endl;
                *solar << "                 <model file=\"saturnRing2.3d\" r=\"0.8\" g=\"0.4\" b=\"0\" />" << endl;
                *solar << "                 <model file=\"saturnRing3.3d\" r=\"0.96\" g=\"0.87\" b=\"0.7\" />" << endl;
                *solar << "             </models>" << endl;
                *solar << "         </group>" << endl;
                *solar << "         <group>" << endl;
                *solar << "             <scale x=\"" << prp << "\" y=\"" << prp << "\" z=\"" << prp << "\" />" << endl;
                *solar << "             <rotate angle=\"" << angleMoons << "\" axisX=\"0\" axisY=\"1\" axisZ=\"0\" />" << endl;
                *solar << "             <translate x=\"" << plD[10] << "\" y=\"0\" z=\"0\" />" << endl;
                *solar << "             <scale x=\"" << plProp[10] << "\" y=\"" << plProp[10] << "\" z=\"" << plProp[10] << "\" />" << endl;
                *solar << "             <models>" << endl;
                *solar << "                 <model file=\"smallPlanets.3d\" r=\"" << colors[10].X() << "\" g=\"" << colors[10].Y() << "\" b=\"" << colors[10].Z() << "\" />" << endl;
                *solar << "             </models>" << endl;
                *solar << "         </group>" << endl;
                angleMoons += angleMoons;
                break;
        }
        *solar << "     </group>" << endl;
    }
}

void genTrajectories(ostringstream* solar){
    ostringstream file;
    file << annulus(360, 360+2, 1, 5000); // Baseado no da Terra
    string pF { "trajectories.3d" };
    dumpFile(file, pF);

    for(int i { 0 }; i < 9; i++){
        float prop { plD[i]/plD[2] };
        *solar << "     <group>" << endl;
        *solar << "         <scale x=\"" << prop << "\" y=\"" << prop << "\" z=\"" << prop << "\" />" << endl;
        *solar << "         <models>" << endl;
        *solar << "             <model file=\"" << pF << "\" r=\"1\" g=\"1\" b=\"1\" />" << endl;
        *solar << "         </models>" << endl;
        *solar << "     </group>" << endl;
    }
}



void genSolarSystem(ostringstream* solar){
    genTrajectories(solar);
    genStars(solar);
    genSmallSizePlanets(solar);
    genBigSizePlanets(solar);
}

int main(int argc, char* argv[]){
    if(argc < 2){
        cerr << "Usage: ./solarSysGen <filename>.xml" << endl;
        return 1;
    }
    ostringstream solar;
    solar << "<scene>" << endl;
    solar << "  <group>" << endl;

    genSolarSystem(&solar);

    solar << "  </group>" << endl;
    solar << "</scene>" << endl;
    dumpFile(solar,argv[1]);
    return 0;
}