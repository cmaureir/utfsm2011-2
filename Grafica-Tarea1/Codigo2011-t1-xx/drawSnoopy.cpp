/*	drawSnoopy.cpp
	this programs draws Snoopy on a window*/

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <fstream>
//#include <windows.h>
#include <sys/stat.h>
using namespace std;

GLsizei wh = 600;
GLsizei ww = 600;
GLsizei swh = 400;
GLsizei sww = 400;
GLfloat xgs = 1, ygs = 1,xgp = 0, ygp = 0; //Global Scale and Global Position for Moving Snoopy
GLfloat xs = 1, ys = 1; //Global Scale for Static Snoopy
GLdouble aspect_ratio_w = 1.0;
GLdouble aspect_ratio_h = 1.0;

bool existeArchivo(string nombreArchivo)
{
	struct stat stArchivoInfo;
	if(stat(nombreArchivo.c_str(),&stArchivoInfo))
	{	   cout << "No se puede abrir el archivo snoopy3.txt" << endl;
			getchar();
			exit(0);
	}
	return true;
}


/* DisplaySnoopy(width scale, 
 *		height scale, 
 *		x position, 
 *		y position
 * ) */ 
void DisplaySnoopy(GLfloat xls, GLfloat yls, GLfloat xlp, GLfloat ylp)
{
	char lineFill;
	GLfloat xj, yj, minx = 0, miny = 0, maxx = 0, maxy = 0;
	int j, nroPuntos;
	fstream inStream;

	existeArchivo("2011-2-cg-snoopy.txt");
	ifstream datos("2011-2-cg-snoopy.txt");
	glClear(GL_COLOR_BUFFER_BIT);
	glTranslatef(xlp,ylp,0);
	glScalef(5.0*xls,5.0*yls, 1.0);
	do
	{
		datos >> nroPuntos >> lineFill;
		if(lineFill == 'l') glBegin(GL_LINE_STRIP);
		else glBegin(GL_POLYGON);
		for(j = 1; j <= nroPuntos; j++)
		{
			datos >> xj >> yj;
			glVertex2f(xj, yj);
			if (xj < minx)
				minx = xj;
			else if (xj > maxx)
				maxx = xj;
			if (yj < miny)
				miny = yj;
			else if (yj > maxy)
				maxy = yj;
		}
		glEnd();
	} while((xj = datos.get()) != EOF);

	/*
	 * Dibujado de rectangulo alrededor de Snoopy
	 */
	glBegin(GL_LINE_STRIP);
		glVertex2f(minx-5, maxy+5);
		glVertex2f(maxx+5, maxy+5);
		glVertex2f(maxx+5, miny-5);
		glVertex2f(minx-5, miny-5);
		glVertex2f(minx-5, maxy+5);
	glEnd();

	glutSwapBuffers();
}


int staticS;

void displays(void)
{	
	glMatrixMode(GL_MODELVIEW);
	gluOrtho2D(0.0, (GLdouble)sww * aspect_ratio_w, 0.0, (GLdouble)swh * aspect_ratio_h);
	DisplaySnoopy((GLfloat)xs/2,(GLfloat)ys/2, (GLfloat)sww/4, (GLfloat)swh/4);
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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (w < h)
	{
		aspect_ratio_h = 1.0 /((float)w / h);
		aspect_ratio_w = 1.0;
	}
	else
	{
		aspect_ratio_h = 1.0;
		aspect_ratio_w = (float)w / h;
	}

}


/*	Main Loop
	Open window with initial window size, title bar, 
	RGBA display mode, and handle input events.	*/
int main(int argc, char** argv)
{	

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize	 (sww, swh); // window size
	glutInitWindowPosition (50, 50); // window position on screen

	staticS=glutCreateWindow("Static Snoopy");
	
	myinit();
	glutDisplayFunc(displays); 
	glutReshapeFunc(myReshape);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize	 (ww, wh);  // window size
	glutInitWindowPosition (400, 50); // window position on screen

	glutIdleFunc(refreshDisplay);
	glutMainLoop();
}
