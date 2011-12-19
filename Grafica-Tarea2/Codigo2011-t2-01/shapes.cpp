#include <GL/glut.h> 
#include <stdio.h>
#include <stdlib.h>

#define N 100

int shapes_number = 0;

struct shapes
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat size;
} shapes[N];

void addShape()
{
	shapes_number++;

	shapes[shapes_number].x = 0.0f;
	shapes[shapes_number].y = 0.0f;
	shapes[shapes_number].z = -5.0f;

	shapes[shapes_number].r = (GLfloat)(rand() % 100) / 100.0f; 
	shapes[shapes_number].g = (GLfloat)(rand() % 100) / 100.0f;
	shapes[shapes_number].b = (GLfloat)(rand() % 100) / 100.0f;

	shapes[shapes_number].size = 1.0f;
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
		case 'a': // Add a new shape!
			addShape();
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
	glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity();

	for (i = 0; i < N; i++)
	{
		glColor3f(shapes[i].r,shapes[i].g,shapes[i].b);
		glTranslatef(shapes[i].x, shapes[i].y, shapes[i].z); 
		glutSolidCube(shapes[i].size);
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
	glutInitDisplayMode (GLUT_SINGLE);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("Shapes");

	// Creating first shape!
	addShape();

	glutDisplayFunc(drawShapes);
	
	glutReshapeFunc(reshape);
 
	glutKeyboardFunc(keys);

	glutIdleFunc(drawShapes);
	
	glutMainLoop();
}
