#include <GL/glut.h> 
#include <stdio.h>
#include <stdlib.h>

#define N 100

int shapes_number = 0;

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
	enum shapeTypes type; 
} shapes[N];

void addShape(enum shapeTypes type)
{
	shapes_number++;

	shapes[shapes_number-1].x = 0.0f;
	shapes[shapes_number-1].y = 0.0f;
	shapes[shapes_number-1].z = -10.0f;

	shapes[shapes_number-1].r = (GLfloat)(rand() % 100) / 100.0f; 
	shapes[shapes_number-1].g = (GLfloat)(rand() % 100) / 100.0f;
	shapes[shapes_number-1].b = (GLfloat)(rand() % 100) / 100.0f;

	shapes[shapes_number-1].size = 1.0f;

	shapes[shapes_number-1].type = type;

}

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
		case 27: // Exit
			exit(0);
			break;
	}
}

void drawShapes()
{
	int i=0;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	for (i = 0; i < shapes_number; i++)
	{
		glLoadIdentity();
		glColor3f(shapes[i].r,shapes[i].g,shapes[i].b);
		glTranslatef(shapes[i].x, shapes[i].y, shapes[i].z);

		switch(shapes[i].type)
		{
			case cube:
				glutSolidCube(shapes[i].size);
				break;
			case sphere:
				glutSolidSphere(shapes[i].size/2, 100*shapes[i].size, 100*shapes[i].size);
				break;
			case cone:
				glutSolidCone(shapes[i].size/2, shapes[i].size*3, 100*shapes[i].size, 100*shapes[i].size);
				break;
			case torus:
				glutSolidTorus(shapes[i].size/8, shapes[i].size/2, 100*shapes[i].size, 100*shapes[i].size);
				break;
			case teapot:
				glutSolidTeapot(shapes[i].size);
				break;
		}
	}

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

	// Creating first shape!
	addShape(cube);

	glutDisplayFunc(drawShapes);
	
	glutReshapeFunc(reshape);
 
	glutKeyboardFunc(keys);

	glutIdleFunc(drawShapes);
	
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
}
