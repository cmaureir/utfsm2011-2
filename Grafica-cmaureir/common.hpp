#ifndef COMMON_H
#define COMMON_H
#include <GL/glut.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

extern GLsizei swh;
extern GLsizei sww;
extern GLsizei swz;
extern GLfloat xgs, ygs,xgp, ygp;
extern GLfloat xs, ys;

struct body {
    int id;
    double x,y,z;
};

extern int n, it;
extern int alpha;
extern int j;
extern float x_max, y_max, z_max;
extern float x_min, y_min, z_min;
extern vector<body> bodies;
extern vector<body> positions;
extern int staticS;
extern float zoom;
#endif
