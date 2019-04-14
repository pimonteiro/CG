#ifndef __MATRIX_H__
#define __MATRIX_H__

void buildRotMatrix(float *, float *, float *, float *);
void cross(float *, float *, float *);
void normalize(float *);
float length(float *);
void multMatrixVector(float *, float *, float *);

#endif