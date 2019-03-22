#include <sstream>
#include <iostream>
#include "../generator/headers/sphere.h"
#include "../generator/headers/outputAux.h"


#define SIZE    5
#define STARSTACKS  100
#define BIGSTACKS   50
#define SMALLSTACKS  10


#define DMERCURY    150
#define DSATTELITE  20

using namespace std;

//"mercury", "venus", "earth", "mars", "pluto", "jupiter", "saturn", "uranus", "neptune", "moon", "titan", "io", "europa", "callisto"
double plProp[14] {1.38, 1.95, 2.3, 1.53, 1.18, 11.60, 10.40, 5.04, 4.88, 0.7, 1.45, 0.95,0.6, 1.38};
double plD[14] {DMERCURY, 1.7*DMERCURY, 2.4*DMERCURY, 3*DMERCURY, 8.8*DMERCURY, 4.2*DMERCURY, 5.9*DMERCURY, 7*DMERCURY, 8*DMERCURY, DSATTELITE, 3.5*DSATTELITE, 3.5*DSATTELITE, 4.5*DSATTELITE, 5.4*DSATTELITE}; //Falta ter em conta solar a orbita para o colocar no sitio certo

float angle {40};
float angleMoons {60};


void genSmallSizePlanets(ostringstream* solar){
    ostringstream file;
    file << sphere(1.0f * SIZE, SMALLSTACKS, SMALLSTACKS);
    string pF {"smallPlanets.3d" };
    dumpFile(file, pF);

    for(int i { 0 }; i < 5; i++){
        *solar << "<group>" << endl;
        float ang;
        if(i == 4) ang = angle*9;
        else ang = angle*i;
        *solar << "     <rotate angle=\"" << ang << "\" axisX=\"0\" axisY=\"1\" axisZ=\"0\" />" << endl;
        *solar << "     <translate x=\"" << plD[i] << "\" y=\"0\" z=\"0\"" << "/>" << endl;
        *solar << "     <scale x=\"" << plProp[i] << "\" y=\"" << plProp[i] << "\" z=\"" << plProp[i] << "\" />" << endl;
        *solar << "     <models>" << endl;
        *solar << "         <model file=\"" << pF << "\" />" << endl;
        *solar << "     </models>" << endl;
        if(i == 2){
            double prp { (1.0f/plProp[i]) };
            *solar << "         <group>" << endl;
            *solar << "             <scale x=\"" << prp << "\" y=\"" << prp << "\" z=\"" << prp << "\" />" << endl;
            *solar << "             <rotate angle=\"" << angleMoons << "\" axisX=\"0\" axisY=\"1\" axisZ=\"0\" />" << endl;
            *solar << "             <translate x=\"" << plD[9] << "\" y=\"0\" z=\"0\"" << "/>" << endl;
            *solar << "             <scale x=\"" << plProp[9] << "\" y=\"" << plProp[9] << "\" z=\"" << plProp[9] << "\" />" << endl;
            *solar << "             <models>" << endl;
            *solar << "                 <model file=\"smallPlanets.3d\" />" << endl;
            *solar << "             </models>" << endl;
            *solar << "         </group>" << endl;
        }
        *solar << "</group>" << endl;
    }
}

void genStars(ostringstream* solar){
    string s1 { "sun.3d" };
    float s1Prop { 24 };

    ostringstream file;
    file << sphere(1.0f * SIZE, STARSTACKS, STARSTACKS);
    dumpFile(file,s1);

    *solar << "<group>" << endl;
    *solar << " <scale x=\"" << s1Prop << "\" y=\"" << s1Prop << "\" z=\"" << s1Prop << "\" />" << endl;
    *solar << "     <models>" << endl;
    *solar << "         <model file=\"" << s1 <<  "\"/>" << endl;
    *solar << "     </models>" << endl;
    *solar << "</group>" << endl;
}

void genBigSizePlanets(ostringstream* solar){
    ostringstream file;
    file << sphere(1.0f * SIZE, BIGSTACKS, BIGSTACKS);
    string pF { "bigPlanets.3d" };
    dumpFile(file, pF);

    for(int i { 5 }; i < 9; i++){
        *solar << "<group>" << endl;
        *solar << "     <rotate angle=\"" << angle*i << "\" axisX=\"0\" axisY=\"1\" axisZ=\"0\" />" << endl;
        *solar << "     <translate x=\"" << plD[i] << "\" Y=\"0\" Z=\"0\"" << "/>" << endl;
        *solar << "     <scale x=\"" << plProp[i] << "\" y=\"" << plProp[i] << "\" z=\"" << plProp[i] << "\" />" << endl;
        *solar << "     <models>" << endl;
        *solar << "         <model file=\"" << pF << "\" />" << endl;
        *solar << "     </models>" << endl;
        switch (i) {
            case 5:
                for(int j {0}; j < 3; j++){
                    float prp = (1.0f/plProp[i]);
                    *solar << "     <group>" << endl;
                    *solar << "         <scale x=\"" << prp << "\" y=\"" << prp << "\" z=\"" << prp << "\" />" << endl;
                    *solar << "         <rotate angle=\"" << angleMoons << "\" axisX=\"0\" axisY=\"1\" axisZ=\"0\" />" << endl;
                    *solar << "         <translate x=\"" << plD[11 + j] << "\" y=\"0\" z=\"0\" />" << endl;
                    *solar << "         <scale x=\"" << plProp[11+j] << "\" y=\"" << plProp[11+j] << "\" z=\"" << plProp[11+j] << "\" />" << endl;
                    *solar << "         <models>" << endl;
                    *solar << "             <model file=\"smallPlanets.3d\" />" << endl;
                    *solar << "         </models>" << endl;
                    *solar << "     </group>" << endl;
                    angleMoons += angleMoons;
                }
                break;
            case 6:
                float prp = (1.0f/plProp[i]);
                *solar << "     <group>" << endl;
                *solar << "         <scale x=\"" << prp << "\" y=\"" << prp << "\" z=\"" << prp << "\" />" << endl;
                *solar << "         <rotate angle=\"" << angleMoons << "\" axisX=\"0\" axisY=\"1\" axisZ=\"0\" />" << endl;
                *solar << "         <translate x=\"" << plD[10] << "\" y=\"0\" z=\"0\" />" << endl;
                *solar << "         <scale x=\"" << plProp[10] << "\" y=\"" << plProp[10] << "\" z=\"" << plProp[10] << "\" />" << endl;
                *solar << "         <models>" << endl;
                *solar << "             <model file=\"smallPlanets.3d\" />" << endl;
                *solar << "         </models>" << endl;
                *solar << "     </group>" << endl;
                angleMoons += angleMoons;
                break;
        }
        *solar << "</group>" << endl;
    }
}


void genSolarSystem(ostringstream* solar){
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
    solar << "<group>" << endl;

    genSolarSystem(&solar);

    solar << "</group>" << endl;
    solar << "</scene>" << endl;
    dumpFile(solar,argv[1]);
    return 0;
}