#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;
#define N 100

GLfloat own_degree = 0.0f;
int spin_speed = 4;
int shapes_number = 0;

bool lights = true;
bool light0 = true;
bool light1 = false;

enum shapeTypes {cube = 1, sphere, cone, torus, teapot} type;
struct shape
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat size;
	GLfloat origin_degree;
	enum shapeTypes type;
} shapes[N];

void addShape(enum shapeTypes type)
{
	shapes_number++;

	// Initial coordinates.
	//   z has a differente coordinate, because the camera is on z=0
	shapes[shapes_number-1].x = 0.0f;
	shapes[shapes_number-1].y = 0.0f;
	shapes[shapes_number-1].z = -10.0f;

	// Set random color to the shape
	shapes[shapes_number-1].r = (GLfloat)(rand() % 100) / 100.0f;
	shapes[shapes_number-1].g = (GLfloat)(rand() % 100) / 100.0f;
	shapes[shapes_number-1].b = (GLfloat)(rand() % 100) / 100.0f;

	// Set size and type of the shape
	shapes[shapes_number-1].size = 1.0f;
	shapes[shapes_number-1].type = type;

	// Set last shape degree according to the origin
	shapes[shapes_number-2].origin_degree = atan2(shapes[shapes_number-2].y, shapes[shapes_number-2].x);

}

// Keys function to assign actions.
void keys(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'x':
			shapes[shapes_number-1].x--;
			break;
		case 'X':
			shapes[shapes_number-1].x++;
			break;
		case 'y':
			shapes[shapes_number-1].y--;
			break;
		case 'Y':
			shapes[shapes_number-1].y++;
			break;
		case 'z':
			shapes[shapes_number-1].z--;
			break;
		case 'Z':
			shapes[shapes_number-1].z++;
			break;
		case 's':
			shapes[shapes_number-1].size -= 0.1f;
			break;
		case 'S':
			shapes[shapes_number-1].size += 0.1f;
			break;
		case '1':
			addShape(cube);
			break;
		case '2':
			addShape(sphere);
			break;
		case '3':
			addShape(cone);
			break;
		case '4':
			addShape(torus);
			break;
		case '5':
			addShape(teapot);
			break;
		case '8':
			if (lights)
			{
				glDisable(GL_LIGHT0);
				glDisable(GL_LIGHT1);
				lights = false;
			}
			else
			{
				glEnable(GL_LIGHT0);
				glEnable(GL_LIGHT1);
				lights = true;
			}
			break;
		case '9':
			if (light0)
			{
				glDisable(GL_LIGHT0);
				light0 = false;
				if (!light1)
					lights = false;
			}
			else
			{
				glEnable(GL_LIGHT0);
				light0 = true;
				if(light1)
					lights = true;
			}
			break;
		case '0':
			if (light1)
			{
				glDisable(GL_LIGHT1);
				light1 = false;
				if(!light0)
					lights = false;
			}
			else
			{
				glEnable(GL_LIGHT1);
				light1 = true;
				if(light0)
					lights = true;
			}
			break;
		case 27: // Exit
			exit(0);
			break;
	}
}

void drawShapes()
{
	int i=0;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// This function call fix the buffer error of place an object over another
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	if (lights)
	{
		if (light0)
		{
			GLfloat position0[] = {10, 10, 5};
			glLightfv(GL_LIGHT0, GL_POSITION, position0);
		}
		if (light1)
		{
			GLfloat position1[] = {-10, 10, 5};
			glLightfv(GL_LIGHT1, GL_POSITION, position1);
		}
	}

	for (i = 0; i < shapes_number; i++)
	{
		glLoadIdentity();
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glColor3f(shapes[i].r,shapes[i].g,shapes[i].b);
		if (i < shapes_number-1)
			glRotatef(shapes[i].origin_degree, 0.0, 0.0, 1.0);
		glTranslatef(shapes[i].x, shapes[i].y, shapes[i].z);
		glRotatef(own_degree, 0.0, 1.0, 0.0);

		// Premade figures
		switch(shapes[i].type)
		{
			case cube:
				// The argument is the length of each edge.
				glutSolidCube(shapes[i].size);
				break;
			case sphere:
				// The arguments are: radius length, subdivisions around Z, subdivision along Z
				glutSolidSphere(shapes[i].size/2, 100*shapes[i].size, 100*shapes[i].size);
				break;
			case cone:
				// The arguments are: base, height, subdivisions around  Z, subdivisions along Z
				glutSolidCone(shapes[i].size/2, shapes[i].size*3, 100*shapes[i].size, 100*shapes[i].size);
				break;
			case torus:
				// The arguments are: inner radius, outer radius, sides per radial section, radial divisions
				glutSolidTorus(shapes[i].size/8, shapes[i].size/2, 100*shapes[i].size, 100*shapes[i].size);
				break;
			case teapot:
				// The argument is the relative size of the teapot
				glutSolidTeapot(shapes[i].size);
				break;
		}
		shapes[i].origin_degree += spin_speed;
		shapes[i].origin_degree = (int)shapes[i].origin_degree % 360;
	}

	own_degree += spin_speed/4;
	own_degree = (int)own_degree % 360;

	glFlush();
}

void reshape (int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

int main (int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize (640, 480);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("Shapes");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	GLfloat ambient[] = {0.1, 0.1, 0.1, 1.0};
	GLfloat diffuse[] = {0.7, 0.7, 0.7, 1.0};
	GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

	glEnable(GL_LIGHT0); // Turning on Light0 by default

	GLfloat param[] = {0.5, 0.5, 0.5};
	glLightModelfv(GL_LIGHT_MODEL_COLOR_CONTROL, param);

	addShape(cube); // Creating first shape by default

	glutDisplayFunc(drawShapes);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keys);
	glutIdleFunc(drawShapes);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
