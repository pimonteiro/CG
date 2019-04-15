#include "headers/bezierPatch.h"
#include "headers/outputAux.h"
#include "../engine/headers/matrix.h"

#include <iostream>
#include <sstream>
#include <fstream>

void getBezierPoint(float u, float v, float *pos, float p[16][3]) {

    // catmull-rom matrix
    float m[4][4] {	{-1.0f, 3.0f, -3.0f, 1.0f},
                         { 3.0f, -6.0f,  3.0f, 0.0f},
                         {-3.0f,  3.0f,  0.0f,  0.0f},
                         { 1.0f,  0.0f,  0.0f,  0.0f}};

    float PPx[4][4] {
            {p[0][0], p[1][0], p[2][0], p[3][0]},
            {p[4][0], p[5][0], p[6][0], p[7][0]},
            {p[8][0], p[9][0], p[10][0], p[11][0]},
            {p[12][0], p[13][0], p[14][0], p[15][0]}
    };
    float PPy[4][4] {
            {p[0][1], p[1][1], p[2][1], p[3][1]},
            {p[4][1], p[5][1], p[6][1], p[7][1]},
            {p[8][1], p[9][1], p[10][1], p[11][1]},
            {p[12][1], p[13][1], p[14][1], p[15][1]}
    };
    float PPz[4][4] {
            {p[0][2], p[1][2], p[2][2], p[3][2]},
            {p[4][2], p[5][2], p[6][2], p[7][2]},
            {p[8][2], p[9][2], p[10][2], p[11][2]},
            {p[12][2], p[13][2], p[14][2], p[15][2]}
    };


    float V[4] {v*v*v,v*v,v,1};
    float U[4] {u*u*u,u*u,u,1};
    // Compute MTV = M(trans) *  V
    float MTV[4];
    multMatrixVector(m[0],V,MTV);

    // Compute MTVP = MTV * P
    float MTVP[3][4];
    multMatrixVector(PPx[0],MTV,MTVP[0]);
    multMatrixVector(PPy[0],MTV,MTVP[1]);
    multMatrixVector(PPz[0],MTV,MTVP[2]);

    // Compute MTVPM = MTVP * M
    float MTVPM[3][4];
    for(int i {0}; i < 4; i++){
        multMatrixVector(m[0],MTVP[i],MTVPM[i]);
    }

    // Compute MTVPMU = MTVPM * U
    for(int i {0}; i < 3; i++){
        pos[i] = U[0] * MTVPM[i][0] + U[1] * MTVPM[i][1] + U[2] * MTVPM[i][2] + U[3] * MTVPM[i][3];
    }
}

std::string getBezierTriangles(int div, int n, int index[][16], float points[][3]) {
    std::ostringstream os;
    std::ostringstream head;
    int total {0};
    float inc { 1.0f/div };
    for(int i {0}; i < n; i++){
        for(int u {0}; u < div; u++){
            for(int v {0}; v < div; v++){
                float pos0[3];
                float pos1[3];
                float pos2[3];
                float pos3[3];
                float pu { (float) u / div };
                float pv { (float) v / div };

                float pI[16][3];
                for(int c {0}; c < 16; c++){
                    pI[c][0] = points[index[i][c]][0];
                    pI[c][1] = points[index[i][c]][1];
                    pI[c][2] = points[index[i][c]][2];
                }

                getBezierPoint(pu, pv, pos0, pI);
                getBezierPoint(pu+inc, pv, pos1, pI);
                getBezierPoint(pu, pv+inc, pos2, pI);
                getBezierPoint(pu+inc, pv+inc, pos3, pI);

                os << writePoint(pos0[0],pos0[1],pos0[2]);
                os << writePoint(pos1[0],pos1[1],pos1[2]);
                os << writePoint(pos2[0],pos2[1],pos2[2]);
                os << writePoint(pos2[0],pos2[1],pos2[2]);
                os << writePoint(pos1[0],pos1[1],pos1[2]);
                os << writePoint(pos3[0],pos3[1],pos3[2]);
                total += 6;
            }
        }
    }
    head << total << std::endl;
    head << os.str() << std::endl;

    return head.str();
}



std::string bezierPatch(std::string filename, int div) {
    // Parse file
    std::ifstream file;
    file.open(filename.c_str());
    if (!file){
        std::cerr << "Unable to open file. " << std::endl;
        exit(1);
    }

    //Read number of patches
    std::string line;
    std::getline(file, line);
    int n { atoi(line.c_str()) };
    int index[n][16];

    //Read indexes of each patch
    for(int i {0}; i < n; i++){
        getline(file,line);
        std::stringstream ss(line);
        int j {0};
        while(j < 16){
            std::string sub;
            getline(ss,sub,',');
            index[i][j++] = atoi(sub.c_str());
        }
    }

    //Read all points
    std::getline(file,line);
    int n_points { atoi(line.c_str())};
    float points[n_points][3];
    for(int i {0}; i < n_points; i++){
        float x, y, z;
        char c[2];
        std::getline(file, line);
        std::stringstream iss(line);
        if(!(iss >> x >> c >> y >> c >> z)){
            std::cerr << "Bad format on points. " << std::endl;
            exit(1);
        }
        points[i][0] = x;
        points[i][1] = y;
        points[i][2] = z;
    }
    file.close();

    return getBezierTriangles(div, n, index, points);   
}