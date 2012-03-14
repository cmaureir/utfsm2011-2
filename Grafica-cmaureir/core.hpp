#ifndef CORE_HPP
#define CORE_HPP
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

// GL Variables
extern GLsizei sww, swh, swz;   // window sizes
extern GLdouble wleft, wright, wbottom, wtop, wnear, wfar; // Orthographic matrix parameters
extern GLfloat sizes[2];   // Point ARB size
extern GLuint g_textureID; // Texture id

// Vector variables
extern vector<body> bodies;    // bodies vector
extern vector<body> positions; // bodies new positions vector

// Variables
extern int n, it, j, r;
extern int alpha; // Maximization parameter.
extern int window_id;
extern float quadratic[3]; // Point distance attenuation
extern float angle_theta, angle_phi; // Mouse motion camera angles
extern float eye_x, eye_y, eye_z;    // LookAt Eye coordinates
extern float dir_x, dir_y, dir_z;    // LookAt Dir coordinates
extern float up_x, up_y, up_z;       // LookAt Up  coordinates
extern float zoom;

// Functions
void init_var(void);
void init(void);
void read_files(void);
void read_info(string path);
void read_input(string path);
void read_results(string path);
void DisplayBodies(void);
void refresh(void);
void reshape(int w, int h);
void keys(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void mouse_motion(int x, int y);
#endif
