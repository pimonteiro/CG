#include <sstream>
#include <iostream>
#include <cmath>
#include <vector>
#niclude <string>
#include "../generator/headers/sphere.h"
#include "../generator/headers/outputAux.h"
#include "../generator/headers/annulus.h"
#include "../generator/headers/bezierPatch.h"
#include "../lib/headers/point.h"


#define SIZE    5
#define STARSTACKS  100
#define BIGSTACKS   50
#define SMALLSTACKS  10


#define DMERCURY    150
#define DSATTELITE  20

#define YEARTOSEC       6*1000 // Represented in seconds

using namespace std;

//"mercury", "venus", "earth", "mars", "pluto", "jupiter", "saturn", "uranus", "neptune", "moon", "titan", "io", "europa", "callisto"
double plProp[14] {1.38, 1.95, 2.3, 1.53, 1.18, 11.60, 10.40, 5.04, 4.88, 0.7, 1.45, 0.95, 0.6, 1.38};
double plD[14] {DMERCURY, 1.7 * DMERCURY, 2.4 * DMERCURY, 3 * DMERCURY, 8.8 * DMERCURY, 4.2 * DMERCURY, 5.9 * DMERCURY, 7 * DMERCURY, 8 * DMERCURY, DSATTELITE, 3.5 * DSATTELITE, 3.5 * DSATTELITE, 4.5 * DSATTELITE, 5.4 * DSATTELITE};
Point colors[14] {Point(0.36, 0.36, 0.36), Point(0.8, 0.5, 0.2), Point(0.31, 0.65, 0.76), Point(0.55, 0.15, 0), Point(0.93, 0.85, 0.68), Point(0.93, 0.8, 0.38), Point(0.93, 0.86, 0.51),
              Point(0.61, 0.77, 0.89), Point(0.23, 0.35, 0.58), Point(0.84, 0.84, 0.84), Point(0.93, 0.8, 0.38), Point(0.93, 0.85, 0.51), Point(0.93, 0.57, 0.13), Point(0.27, 0.27, 0.27)
};
float plTime[14] {YEARTOSEC * 0.2, YEARTOSEC * 0.6, YEARTOSEC * 1, YEARTOSEC * 1.9, YEARTOSEC * 248, YEARTOSEC * 11.9, YEARTOSEC * 29.5, YEARTOSEC * 84, YEARTOSEC * 164.8, YEARTOSEC, YEARTOSEC, YEARTOSEC, YEARTOSEC, YEARTOSEC};
string textures[14] {"","","earth.png",""};

float angle {40};
float angleMoons {60};



void planetOrbitalPoints(float r, ostringstream *solar, float prop) {
        for (int i { 0 }; i < 8; i++) {
                float ang {static_cast<float>((M_PI) / 4.0f) *i };
                float x { r * cos(ang) *prop};
                float z { r * sin(ang) *prop};
                *solar << "         <point x=\"" << x << "\" y=\"0\" z=\"" << z << "\" />" << endl;
        }
}


void genSmallSizePlanets(ostringstream *solar) {
        ostringstream file;
        file << sphere(1.0f * SIZE, SMALLSTACKS, SMALLSTACKS);
        string pF {"smallPlanets.3d" };
        dumpFile(file, pF);

        for (int i { 0 }; i < 5; i++) {
                *solar << "     <group>" << endl;
                float ang;

                if (i == 4)
                        ang = angle * 9;
                else
                        ang = angle * i;

                *solar << "         <rotate angle=\"" << ang << "\" axisX=\"0\" axisY=\"1\" axisZ=\"0\" />" << endl;
                *solar << "         <translate time=\"" << plTime[i] << "\" selfRotate=\"0\" >" << endl;
                planetOrbitalPoints(plD[i], solar, 1);
                *solar << "         </translate>" << endl;
                *solar << "         <scale x=\"" << plProp[i] << "\" y=\"" << plProp[i] << "\" z=\"" << plProp[i] << "\" />" << endl;
                *solar << "         <models>" << endl;
                *solar << "             <model file=\"" << pF << "\" type=\"diffuse\" r=\"" << colors[i].X() << "\" g=\"" << colors[i].Y() << "\" b=\"" << colors[i].Z() << "\" />" << endl;
                *solar << "         </models>" << endl;

                if (i == 2) {
                        float prp { static_cast<float>(1.0f / plProp[i]) };
                        *solar << "             <group>" << endl;
                        *solar << "                 <rotate angle=\"" << angleMoons << "\" axisX=\"0\" axisY=\"1\" axisZ=\"0\" />" << endl;
                        *solar << "                 <translate time=\"" << plTime[9] << "\" selfRotate=\"0\" >" << endl;
                        planetOrbitalPoints(plD[9], solar, prp);
                        *solar << "                 </translate>" << endl;
                        *solar << "                 <scale x=\"" << prp *plProp[9] << "\" y=\"" << prp *plProp[9] << "\" z=\"" << prp *plProp[9] << "\" />" << endl;
                        *solar << "                 <models>" << endl;
                        *solar << "                     <model file=\"" << pF << "\" r=\"" << colors[9].X() << "\" g=\"" << colors[9].Y() << "\" b=\"" << colors[9].Z() << "\" />" << endl;
                        *solar << "                 </models>" << endl;
                        *solar << "             </group>" << endl;
                }

                *solar << "     </group>" << endl;
        }
}

void genStars(ostringstream *solar) {
        string s1 { "sun.3d" };
        float s1Prop { 24 };
        ostringstream file;
        file << sphere(1.0f * SIZE, STARSTACKS, STARSTACKS);
        dumpFile(file, s1);
        *solar << "     <group>" << endl;
        *solar << "         <scale x=\"" << s1Prop << "\" y=\"" << s1Prop << "\" z=\"" << s1Prop << "\" />" << endl;
        *solar << "         <models>" << endl;
        *solar << "             <model file=\"" << s1 << "\" texture=\"sun.png\" />" << endl;
        *solar << "         </models>" << endl;
        *solar << "     </group>" << endl;
}

void genBigSizePlanets(ostringstream *solar) {
        ostringstream file;
        file << sphere(1.0f * SIZE, BIGSTACKS, BIGSTACKS);
        string pF { "bigPlanets.3d" };
        dumpFile(file, pF);

        for (int i { 5 }; i < 9; i++) {
                *solar << "     <group>" << endl;
                *solar << "         <rotate angle=\"" << angle *i << "\" axisX=\"0\" axisY=\"1\" axisZ=\"0\" />" << endl;
                *solar << "         <translate time=\"" << plTime[i] << "\" selfRotate=\"0\" >" << endl;
                planetOrbitalPoints(plD[i], solar, 1);
                *solar << "         </translate>" << endl;
                *solar << "         <scale x=\"" << plProp[i] << "\" y=\"" << plProp[i] << "\" z=\"" << plProp[i] << "\" />" << endl;
                *solar << "         <models>" << endl;
                *solar << "             <model file=\"" << pF << "\" r=\"" << colors[i].X() << "\" g=\"" << colors[i].Y() << "\" b=\"" << colors[i].Z() << "\" />" << endl;
                *solar << "         </models>" << endl;

                switch (i) {
                case 5:
                        for (int j {0}; j < 3; j++) {
                                float prp { static_cast<float>(1.0f / plProp[i]) };
                                *solar << "         <group>" << endl;
                                *solar << "             <rotate angle=\"" << angleMoons << "\" axisX=\"0\" axisY=\"1\" axisZ=\"0\" />" << endl;
                                *solar << "             <translate time=\"" << plTime[11 + j] << "\" selfRotate=\"0\" >" << endl;
                                planetOrbitalPoints(plD[11 + j], solar, prp);
                                *solar << "             </translate>" << endl;
                                *solar << "             <scale x=\"" << prp *plProp[11 + j] << "\" y=\"" << prp *plProp[11 + j] << "\" z=\"" << prp *plProp[11 + j] << "\" />" << endl;
                                *solar << "             <models>" << endl;
                                *solar << "                 <model file=\"smallPlanets.3d\" r=\"" << colors[11 + j].X() << "\" g=\"" << colors[11 + j].Y() << "\" b=\"" << colors[11 + j].Z() << "\" />" << endl;
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
                        float prp = (1.0f / plProp[i]);
                        *solar << "         <group>" << endl;
                        *solar << "             <rotate angle=\"15\" axisX=\"1\" axisY=\"0\" axisZ=\"0\" />" << endl;
                        *solar << "             <models>" << endl;
                        *solar << "                 <model file=\"saturnRing1.3d\" r=\"0\" g=\"0\" b=\"0.8\" />" << endl;
                        *solar << "                 <model file=\"saturnRing2.3d\" r=\"0.8\" g=\"0.4\" b=\"0\" />" << endl;
                        *solar << "                 <model file=\"saturnRing3.3d\" r=\"0.96\" g=\"0.87\" b=\"0.7\" />" << endl;
                        *solar << "             </models>" << endl;
                        *solar << "         </group>" << endl;
                        *solar << "         <group>" << endl;
                        *solar << "             <rotate angle=\"" << angleMoons << "\" axisX=\"0\" axisY=\"1\" axisZ=\"0\" />" << endl;
                        *solar << "             <translate time=\"" << plTime[10] << "\" selfRotate=\"0\" >" << endl;
                        planetOrbitalPoints(plD[10], solar, prp);
                        *solar << "             </translate>" << endl;
                        *solar << "             <scale x=\"" << prp *plProp[10] << "\" y=\"" << prp *plProp[10] << "\" z=\"" << prp *plProp[10] << "\" />" << endl;
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

void genTrajectories(ostringstream *solar) {
        ostringstream file;
        file << annulus(360, 360 + 2, 1, 5000); // Baseado no da Terra
        string pF { "trajectories.3d" };
        dumpFile(file, pF);

        for (int i { 0 }; i < 9; i++) {
                float prop { static_cast<float>(plD[i] / plD[2]) };
                *solar << "     <group>" << endl;
                *solar << "         <scale x=\"" << prop << "\" y=\"" << prop << "\" z=\"" << prop << "\" />" << endl;
                *solar << "         <models>" << endl;
                *solar << "             <model file=\"" << pF << "\" r=\"1\" g=\"1\" b=\"1\" />" << endl;
                *solar << "         </models>" << endl;
                *solar << "     </group>" << endl;
        }
}


void genComet(ostringstream *solar) {
        ostringstream file;
        file << bezierPatch("teapot-2.patch", 30);
        string pF {"comet.3d"};
        dumpFile(file, pF);
        *solar << "     <group>" << endl;
        *solar << "         <scale x=\"3\" y=\"3\" z=\"3\" />" << endl;
        *solar << "         <translate time=\"" << plTime[10] << "\" selfRotate=\"1\" >" << endl;
        *solar << "             <point x=\"202\" y=\"50\" z=\"0\" />" << endl;
        *solar << "             <point x=\"150\" y=\"50\" z=\"150\" />" << endl;
        *solar << "             <point x=\"75\" y=\"25\" z=\"0\" />" << endl;
        *solar << "             <point x=\"0\" y=\"-50\" z=\"-150\" />" << endl;
        *solar << "             <point x=\"-75\" y=\"-50\" z=\"0\" />" << endl;
        *solar << "             <point x=\"0\" y=\"-50\" z=\"150\" />" << endl;
        *solar << "             <point x=\"75\" y=\"-25\" z=\"0\" />" << endl;
        *solar << "             <point x=\"150\" y=\"50\" z=\"-150\" />" << endl;
        *solar << "         </translate>" << endl;
        *solar << "         <rotate angle=\"-90\" axisX=\"1\" axisY=\"0\" axisZ=\"0\" />" << endl;
        *solar << "         <models>" << endl;
        *solar << "             <model file=\"" << pF << "\" r=\"0.37\" g=\"0.15\" b=\"0.02\" />" << endl;
        *solar << "         </models>" << endl;
        *solar << "     </group>" << endl;
}


void genSolarSystem(ostringstream *solar) {
        //genTrajectories(solar);
        genStars(solar);
        genComet(solar);
        genSmallSizePlanets(solar);
        genBigSizePlanets(solar);
}

int main(int argc, char *argv[]) {
        if (argc < 2) {
                cerr << "Usage: ./solarSysGen <filename>.xml" << endl;
                return 1;
        }

        ostringstream solar;
        solar << "<scene>" << endl;
        solar << "  <group>" << endl;
        genSolarSystem(&solar);
        solar << "  </group>" << endl;
        solar << "</scene>" << endl;
        dumpFile(solar, argv[1]);
        return 0;
}