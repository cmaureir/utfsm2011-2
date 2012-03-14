#include "core.hpp"

// Variable declaration
GLsizei sww, swh, swz;
GLdouble wleft, wright, wbottom, wtop, wnear, wfar;
GLfloat sizes[2];
GLuint g_textureID;

vector<body> bodies;
vector<body> positions;

int n, it, j, r;
int alpha;
int window_id;
float quadratic[3];
float angle_theta, angle_phi;
float eye_x, eye_y, eye_z;
float dir_x, dir_y, dir_z;
float up_x, up_y, up_z;
float zoom;


// Variable initialization
void init_var()
{
    sww = 960; swh = 720; swz = 700;

    wleft   = -(GLdouble)sww; wright = (GLdouble)sww;
    wbottom = -(GLdouble)swh; wtop   = (GLdouble)swh;
    wnear   = -(GLdouble)swz; wfar   = (GLdouble)swz;

    alpha = 50; zoom = 1.0;
    j = 0; r = 10;

    quadratic[0] = 0.0f; quadratic[1] = 0.0f; quadratic[2] = 0.01f;
    angle_theta = 0.0; angle_phi = 0.0;

    eye_x = 0.0; eye_y = 0.0; eye_z = 5.0;
    dir_x = 0.0; dir_y = 0.0; dir_z = 0.0;
    up_x  = 0.0; up_y  = 1.0; up_z  = 0.0;
}

// OpenGL texture initialization
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    // Loading BMP
    Bitmap *image = new Bitmap();
    string texture_file = "texture/particle.bmp";
    if (image->loadBMP(texture_file.c_str()) == false)
    {
      cerr << "Error opening bmp" <<endl;
      exit(0);
    }

    // Enabling 2D texture
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &g_textureID);

    glBindTexture(GL_TEXTURE_2D, g_textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Loading BMP to texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
}

// File reading
void read_files()
{
    read_info("input/256info");
    read_input("input/256init");
    read_results("input/256result");
}

// Information file reading
void read_info(string path)
{
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
        l++;
    }
}

// Initial bodies position
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

// New bodies positions
void read_results(string path)
{
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

// Display the bodies using the texture
void DisplayBodies()
{

    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // Updating camera position
    gluLookAt(eye_x, eye_y, eye_z, dir_x,dir_y, dir_z, up_x, up_y, up_z);
    glTranslatef(0,0,0);

    // Enabling and configuring the BLEND
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_COLOR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glDepthMask(GL_FALSE);
    glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, sizes);

    // Enabling and configuring POINT_SPRITE
    glEnable(GL_POINT_SPRITE_ARB);

    glPointParameterfARB(GL_POINT_SIZE_MAX_ARB, sizes[1]);
    glPointParameterfARB(GL_POINT_SIZE_MIN_ARB, sizes[0] + 7.0f);
    glPointParameterfvARB(GL_POINT_DISTANCE_ATTENUATION_ARB, quadratic);

    glTexEnvi(GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE);

    // White bodies with alpha channel
    glColor4f (1.0f,1.0f,1.0f,0.5f);
    glBindTexture(GL_TEXTURE_2D, g_textureID);

    // Draw points
    glBegin(GL_POINTS);
        for(int i = 0; i <= n; i++)
        {
            glVertex3f( bodies[i].x*alpha*zoom,
                        bodies[i].y*alpha*zoom,
                        bodies[i].z*alpha*zoom);
        }
    glEnd();

    // Disabling environment
    glDisable(GL_POINT_SPRITE_ARB);
    glDisable(GL_BLEND);
}

// Window refresh function
void refresh(void)
{
    glutSetWindow(window_id);

    // Bodies position update
    if (j < it - 1)
    {
        for (int  i=0; i < n; i++)
        {
            bodies[i].x = positions[j].x;
            bodies[i].y = positions[j].y;
            bodies[i].z = positions[j].z;
            j++;
        }
    }
    DisplayBodies();
    glFlush();
}

// Reshape function
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(wleft, wright, wbottom, wtop, wnear, wfar);
}

// Keys functionality
void keys(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'z':
            zoom += 0.1; break;
        case 'Z':
            zoom -= 0.1; break;
        case 27:
            exit(0);
            break;
    }
}

// Mouse functionality
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

// Mouse motion functionality
void mouse_motion(int x, int y)
{
   // Mouse point to angle conversion
   angle_theta = (360.0/swh)*y*3.0;    //3.0 rotations possible
   angle_phi   = (360.0/sww)*x*3.0;

   // Restrict the angles within 0~360 deg (optional)
   if(angle_theta > 360) angle_theta = fmod((double)angle_theta,360.0);
   if(angle_phi   > 360) angle_phi   = fmod((double)angle_phi,360.0);

   // Spherical to Cartesian conversion.
   // Degrees to radians conversion factor 0.0174532
   eye_x = r * sin(angle_theta*0.0174532) * sin(angle_phi*0.0174532);
   eye_y = r * cos(angle_theta*0.0174532);
   eye_z = r * sin(angle_theta*0.0174532) * cos(angle_phi*0.0174532);

   // Reduce angle_theta slightly to obtain another point on the same longitude line on the sphere.
   GLfloat dt = 1.0;
   GLfloat eye_xtemp = r * sin(angle_theta*0.0174532-dt) * sin(angle_phi*0.0174532);
   GLfloat eye_ytemp = r * cos(angle_theta*0.0174532-dt);
   GLfloat eye_ztemp = r * sin(angle_theta*0.0174532-dt) * cos(angle_phi*0.0174532);

   // Connect these two points to obtain the camera's up vector.
   up_x=eye_xtemp-eye_x;
   up_y=eye_ytemp-eye_y;
   up_z=eye_ztemp-eye_z;

   glutPostRedisplay();
}
