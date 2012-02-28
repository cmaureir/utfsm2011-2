#include <GL/glut.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

GLsizei swh = 400;
GLsizei sww = 400;
GLfloat xgs = 1, ygs = 1,xgp = 0, ygp = 0;
GLfloat xs = 1, ys = 1;

struct body {
    int id;
    float x,y,z;
};

void read_info(){

}

void read_input(){

}

void read_results(){

}

float xx[] = {100,100,200};
float yy[] = {100,200,200};
float zz[] = {0,0,0};

void DisplayBodies()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glTranslatef(0,0,0);
    //glScalef(5.0,5.0, 1.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < 3; i++) {
        glVertex3f(xx[i],yy[i],zz[i]);
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

void refreshDisplay(void)
{
    glutSetWindow(staticS);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutPostRedisplay();
}

void myinit(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h); //New viewport
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

}

void update(int value)
{
    xx[0] += 1;
    xx[1] += 1;
    xx[2] += 1;
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);

}
void keys(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'x':
            xx[0] += 20;
            xx[1] += 20;
            xx[2] += 20;
            break;
        case 'y':
            yy[0] += 20;
            yy[1] += 20;
            yy[2] += 20;
            break;
        case 'z':
            zz[0] += 1;
            zz[1] += 1;
            zz[2] += 1;
            break;
    }
}

int main(int argc, char** argv)
{

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(sww, swh); // window size
    glutInitWindowPosition (0, 0); // window position on screen
    staticS=glutCreateWindow("Bodies");

    myinit();
    glutDisplayFunc(displays);
    glutReshapeFunc(myReshape);
    glutTimerFunc(25, update, 0);
    glutKeyboardFunc(keys);
    glutIdleFunc(refreshDisplay);
    glutMainLoop();
}
