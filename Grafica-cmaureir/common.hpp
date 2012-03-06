#ifndef COMMON_H
#define COMMON_H
#include <GL/glut.h>
#include <GL/glext.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "Bitmap.h"
using namespace std;

struct body {
    int id;
    double x,y,z;
};

extern GLsizei sww, swh, swz;
extern GLfloat xgs, ygs,xgp, ygp;
extern GLfloat xs, ys;
extern GLdouble wleft, wright, wbottom, wtop, wnear, wfar;

extern int n, it, j;
extern int alpha;
extern float x_max, y_max, z_max;
extern float x_min, y_min, z_min;
extern vector<body> bodies;
extern vector<body> positions;
extern int window_id;
extern float zoom_x, zoom_y, zoom_z;
#endif
