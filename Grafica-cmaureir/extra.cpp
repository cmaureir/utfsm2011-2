#include "extra.hpp"

GLsizei sww, swh, swz;
GLfloat xgs, ygs, xgp, ygp;
GLfloat xs, ys;

int n, it, j;
int alpha;
float x_max, y_max, z_max;
float x_min, y_min, z_min;
vector<body> bodies;
vector<body> positions;
int window_id;
float zoom;

int axis;
float theta[3];
float eye[3];

void init_var(){
    alpha = 50;
    j = 0;
    swh = 800;
    sww = 800;
    swz = 800;
    xgs = 1, ygs = 1,xgp = 0, ygp = 0;
    xs = 1, ys = 1;
    zoom = 0.5;
}

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
    int i = 0;
    while (info.good() && i < n)
    {
        getline(info,line,' ');
        tmp.id = atoi(line.c_str());

        getline(info,line,' ');
        tmp.x = atof(line.c_str());

        getline(info,line,' ');
        tmp.y = atof(line.c_str());

        getline(info,line,'\n');
        tmp.z = atof(line.c_str());

        bodies.push_back(tmp);
        i++;
    }
}

void read_results(string path){
    ifstream info(path.c_str());
    string line;
    body tmp;
    int i = 0;
    while (info.good() && i < it)
    {
        getline(info,line,' ');
        tmp.id = atoi(line.c_str());

        getline(info,line,' ');
        tmp.x = atof(line.c_str());

        getline(info,line,' ');
        tmp.y = atof(line.c_str());

        getline(info,line,'\n');
        tmp.z = atof(line.c_str());

        positions.push_back(tmp);
        i++;
    }
}

void DisplayBodies()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTranslatef(0,0,0);

    GLfloat sizes[2];
    float quadratic[] =  { 0.0f, 0.0f, 0.01f };
    GLuint g_textureID = 0;

    glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, sizes);
    glEnable( GL_POINT_SPRITE_ARB );
    glPointParameterfARB( GL_POINT_SIZE_MAX_ARB, sizes[1] );
    glPointParameterfARB( GL_POINT_SIZE_MIN_ARB, sizes[0]);
    glPointParameterfvARB( GL_POINT_DISTANCE_ATTENUATION_ARB, quadratic );
    glTexEnvi( GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE );
    Bitmap *image = new Bitmap();
    string texture_file = "texture/particle2.bmp";
    if (image->loadBMP(texture_file.c_str()) == false)
    {
      cout << "Error: " <<endl;
      return;
    }
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &g_textureID);
    glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
    glEnable( GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_COLOR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glDepthMask(GL_FALSE);

    glColor4f (1.0f,1.0f,1.0f,0.3f);
    glBegin(GL_POINTS);
    for(int i = 0; i <= n; i++)
    {
        glBindTexture(GL_TEXTURE_2D, g_textureID);
        glVertex3f( (sww/2.0)+bodies[i].x*alpha,
                    (swh/2.0)+bodies[i].y*alpha,
                              bodies[i].z);
    }
    // Done drawing points
    glEnd();
    glDisable( GL_POINT_SPRITE_ARB );

}


void displays(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluLookAt(10, 10, 10,  0, 0, 0,  0, 0, 1);
    glOrtho(0.0, (GLdouble)sww, 0.0, (GLdouble)swh, -1.0-zoom, 3.5);
    DisplayBodies();
    glutSwapBuffers();
}

void refresh(void)
{
    glutSetWindow(window_id);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutPostRedisplay();

    if ( j < it - 1  ){
        for (int  i=0; i < n; i++) {
            bodies.at(i).x = positions.at(j).x;
            bodies.at(i).y = positions.at(j).y;
            bodies.at(i).z = positions.at(j).z;
            j++;
        }
    }

}


void reshape(int w, int h)
{
    glViewport(0, 0, w, h); //New viewport
    //glMatrixMode(GL_MODELVIEW);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

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
            zoom += 0.5;
            break;
        case 'Z':
            zoom -= 0.5;
            break;
    }
}

void mouse(int button, int state, int x, int y)
{
    cout << "Button: " <<  button << "\t" << "State: " << state << "\t" << "(x,y)=(" << x << "," << y << ")" << endl;
}

void mouse_motion(int x, int y)
{
    cout << "(x,y)=(" << x << "," << y << ")" << endl;
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    read_info("input/256info");
    read_input("input/256init");
    read_results("/home/cmaureir/256result.1b");
}
