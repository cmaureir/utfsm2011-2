#include <GL/glut.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

GLsizei swh = 400;
GLsizei sww = 400;
GLsizei swz = 400;
GLfloat xgs = 1, ygs = 1,xgp = 0, ygp = 0;
GLfloat xs = 1, ys = 1;

struct body {
    int id;
    float x,y,z;
};

// Information
int n;
int it;
float x_max, y_max, z_max;
float x_min, y_min, z_min;
vector<body> bodies;
vector<body> positions;

void read_info(string path){
    ifstream info(path.c_str());
    string line;
    int l = 0;
    while (info.good())
    {
        if (l == 0)
        {
            getline(info,line);
            n = atoi(line.c_str());
        }
        else if (l == 1)
        {
            getline(info,line);
            it = atoi(line.c_str());
        }
        else if (l == 2)
        {
            getline(info, line, ' ');
            getline(info, line, ' ');
            x_min = atof(line.c_str());
            getline(info, line, ' ');
            x_max = atof(line.c_str());
        }
        else if (l == 3)
        {
            getline(info, line, ' ');
            getline(info, line, ' ');
            y_min = atof(line.c_str());
            getline(info, line, ' ');
            y_max = atof(line.c_str());
        }
        else if (l == 4)
        {
            getline(info, line, ' ');
            getline(info, line, ' ');
            z_min = atof(line.c_str());
            getline(info, line, ' ');
            z_max = atof(line.c_str());
        }
        l++;
    }

}

void read_input(string path){
    ifstream info(path.c_str());
    string line;
    body tmp;
    while (info.good())
    {
        getline(info,line,' ');
        tmp.id = atoi(line.c_str());
        getline(info,line,' ');
        tmp.x = atof(line.c_str());
        getline(info,line,' ');
        tmp.y = atof(line.c_str());
        getline(info,line,' ');
        tmp.z = atof(line.c_str());
        bodies.push_back(tmp);
    }
}

void read_results(string path){
    ifstream info(path.c_str());
    string line;
    body tmp;
    while (info.good())
    {
        getline(info,line,' ');
        tmp.id = atoi(line.c_str());
        getline(info,line,' ');
        tmp.x = atof(line.c_str());
        getline(info,line,' ');
        tmp.y = atof(line.c_str());
        getline(info,line,' ');
        tmp.z = atof(line.c_str());
        bodies.push_back(tmp);
    }

}

void DisplayBodies()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glTranslatef(0,0,0);
    glBegin(GL_POINTS);
    for (int i = 0; i < n; i++) {
        glVertex3f((sww/2.0)+bodies[i].x*20,(swh/2.0)+bodies[i].y*20,bodies[i].z);
    }
    glEnd();

    glutSwapBuffers();
}


int staticS;

void displays(void)
{
    glMatrixMode(GL_MODELVIEW);
    gluOrtho2D(0.0, (GLdouble)sww, 0.0, (GLdouble)swh);
    DisplayBodies();
    glutSwapBuffers();
}

void refresh(void)
{
    glutSetWindow(staticS);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutPostRedisplay();

}


void myReshape(int w, int h)
{
    glViewport(0, 0, w, h); //New viewport
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

}
void keys(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'x':
            break;
        case 'y':
            break;
        case 'z':
            break;
    }
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    read_info("input/256info");
    read_input("input/256init");
}

int main(int argc, char** argv)
{

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(sww, swh); // window size
    glutInitWindowPosition (0, 0); // window position on screen
    staticS=glutCreateWindow("Bodies");

    init();
    glutDisplayFunc(displays);
    glutReshapeFunc(myReshape);
    glutKeyboardFunc(keys);
    glutIdleFunc(refresh);
    glutMainLoop();
}
