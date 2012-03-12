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
GLdouble zoom_x, zoom_y, zoom_z;
GLdouble wleft, wright, wbottom, wtop, wnear, wfar;

    GLfloat sizes[2];
    float quadratic[] =  { 0.0f, 0.0f, 0.01f };
    GLuint g_textureID;

int axis;
float theta[3];
float eye[3];
float angle_theta, angle_phi;
float eye_x, eye_y, eye_z;
float dir_x, dir_y, dir_z;
float up_x, up_y, up_z;
int r = 10;
float zoom = 1;
void init_var(){
    alpha = 50; j = 0; angle_theta = 0.0;
    angle_phi = 0.0;
    eye_x = 0.0; eye_y = 0.0; eye_z = 5.0;
    dir_x = 0.0; dir_y = 0.0; dir_z = 0.0;
    up_x = 0.0; up_y = 1.0; up_z = 0.0;
    sww = 960; swh = 720; swz  = 700;
    xgs = 1;   ygs = 1;   xgp  = 0; ygp = 0;
    xs  = 1;   ys  = 1;
    zoom_x  = 0.0; zoom_y = 0.0;  zoom_z = 5;
    wleft   = -(GLdouble)sww; wright = (GLdouble)sww;
    wbottom = -(GLdouble)swh; wtop   = (GLdouble)swh;
    wnear   = -(GLdouble)swz; wfar   = (GLdouble)swz;
}

void read_info(string path){
    ifstream info(path.c_str());
    string line;
    int l = 0;
    while (info.good())
    {
        if (l == 0)
        {
            getline(info,line); n = atoi(line.c_str());
        }
        else if (l == 1)
        {
            getline(info,line); it = atoi(line.c_str());
        }
        else if (l == 2)
        {
            getline(info, line, ' ');
            getline(info, line, ' '); x_min = atof(line.c_str());
            getline(info, line, ' '); x_max = atof(line.c_str());
        }
        else if (l == 3)
        {
            getline(info, line, ' ');
            getline(info, line, ' '); y_min = atof(line.c_str());
            getline(info, line, ' '); y_max = atof(line.c_str());
        }
        else if (l == 4)
        {
            getline(info, line, ' ');
            getline(info, line, ' '); z_min = atof(line.c_str());
            getline(info, line, ' '); z_max = atof(line.c_str());
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
        getline(info,line,' ');  tmp.id = atoi(line.c_str());
        getline(info,line,' ');  tmp.x  = atof(line.c_str());
        getline(info,line,' ');  tmp.y  = atof(line.c_str());
        getline(info,line,'\n'); tmp.z  = atof(line.c_str());

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
        getline(info,line,' ');  tmp.id = atoi(line.c_str());
        getline(info,line,' ');  tmp.x  = atof(line.c_str());
        getline(info,line,' ');  tmp.y  = atof(line.c_str());
        getline(info,line,'\n'); tmp.z  = atof(line.c_str());

        positions.push_back(tmp);
        i++;
    }
}

void DisplayBodies()
{

    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt (eye_x, eye_y, eye_z, dir_x,dir_y, dir_z, up_x, up_y, up_z);
    glTranslatef(0,0,0);


    glEnable( GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_COLOR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glDepthMask(GL_FALSE);
    glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, sizes);

    glEnable( GL_POINT_SPRITE_ARB );
    glPointParameterfARB( GL_POINT_SIZE_MAX_ARB, sizes[1] );
    glPointParameterfARB( GL_POINT_SIZE_MIN_ARB, sizes[0]);
    glPointParameterfvARB( GL_POINT_DISTANCE_ATTENUATION_ARB, quadratic );
    glTexEnvi( GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE );

    glColor4f (1.0f,1.0f,1.0f,0.3f);
    glBindTexture(GL_TEXTURE_2D, g_textureID);
    glBegin(GL_POINTS);
    for(int i = 0; i <= n; i++)
    {
        glVertex3f( bodies[i].x*alpha*zoom,
                    bodies[i].y*alpha*zoom,
                    bodies[i].z*alpha*zoom);
    }
    glEnd();
    glDisable( GL_POINT_SPRITE_ARB );
    //glTranslatef(0,0,0);
    //glColor3f(1,0,0);
    //glutSolidTeapot(100*zoom);
}

void refresh(void)
{
    glutSetWindow(window_id);

    if ( j < it - 1  ){
        for (int  i=0; i < n; i++) {
            bodies.at(i).x = positions.at(j).x;
            bodies.at(i).y = positions.at(j).y;
            bodies.at(i).z = positions.at(j).z;
            j++;
        }
    }
    DisplayBodies();
    //glutSwapBuffers();
    glFlush();
}


void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(wleft, wright, wbottom, wtop, wnear, wfar);
}
void keys(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'z':
            zoom += 0.1; break;
        case 'Z':
            zoom -= 0.1; break;
    }
}

void mouse(int button, int state, int x, int y)
{
    switch(button)
    {
        case 3:
            zoom += 0.1; break;
        case 4:
            zoom -= 0.1; break;

    }
}

void mouse_motion(int x, int y)
{
// Mouse point to angle conversion
   angle_theta = (360.0/swh)*y*3.0;    //3.0 rotations possible
   angle_phi = (360.0/sww)*x*3.0;

// Restrict the angles within 0~360 deg (optional)
   if(angle_theta > 360)angle_theta = fmod((double)angle_theta,360.0);
   if(angle_phi > 360)angle_phi = fmod((double)angle_phi,360.0);

// Spherical to Cartesian conversion.
// Degrees to radians conversion factor 0.0174532
   eye_x = r * sin(angle_theta*0.0174532) * sin(angle_phi*0.0174532);
   eye_y = r * cos(angle_theta*0.0174532);
   eye_z = r * sin(angle_theta*0.0174532) * cos(angle_phi*0.0174532);

// Reduce angle_theta slightly to obtain another point on the same longitude line on the sphere.
   GLfloat dt=1.0;
   GLfloat eye_xtemp = r * sin(angle_theta*0.0174532-dt) * sin(angle_phi*0.0174532);
   GLfloat eye_ytemp = r * cos(angle_theta*0.0174532-dt);
   GLfloat eye_ztemp = r * sin(angle_theta*0.0174532-dt) * cos(angle_phi*0.0174532);

// Connect these two points to obtain the camera's up vector.
   up_x=eye_xtemp-eye_x;
   up_y=eye_ytemp-eye_y;
   up_z=eye_ztemp-eye_z;

   glutPostRedisplay();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    read_info("input/256info");
    read_input("input/256init");
    read_results("input/256result");
    glEnable(GL_DEPTH_TEST);

    Bitmap *image = new Bitmap();
    string texture_file = "texture/particle.bmp";
    if (image->loadBMP(texture_file.c_str()) == false)
    {
      cerr << "Error opening bmp" <<endl;
      return;
    }

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &g_textureID);
    glBindTexture(GL_TEXTURE_2D, g_textureID);
    glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
}
