#include "extra.hpp"

GLsizei swh;
GLsizei sww;
GLsizei swz;
GLfloat xgs, ygs, xgp, ygp;
GLfloat xs, ys;

int n, it;
int alpha;
int j;
float x_max, y_max, z_max;
float x_min, y_min, z_min;
vector<body> bodies;
vector<body> positions;
int staticS;
float zoom;

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

    //glPointSize(3.0f);
    //glBegin(GL_POINTS);

    //    glColor3f(1.0f,0.0f,0.0f);
    //    glPointSize(10.0f);
    //    glVertex3f( (sww/2.0)+bodies[0].x*alpha,
    //                (swh/2.0)+bodies[0].y*alpha,
    //                          bodies[0].z);
    //    glColor3f(1.0f,0.0f,0.0f);
    //    glVertex3f( (sww/2.0)+bodies[1].x*alpha,
    //                (swh/2.0)+bodies[1].y*alpha,
    //                          bodies[1].z);

    //glEnd();

    glPointSize(1.0f);
    glBegin(GL_POINTS);
        glPointSize(1.0f);
        glColor3f(1.0f,1.0f,1.0f);
        for (int i = 0; i <= n; i++) {
            glVertex3f( (sww/2.0)+bodies[i].x*alpha,
                        (swh/2.0)+bodies[i].y*alpha,
                                  bodies[i].z);
        }
    glEnd();

    glutSwapBuffers();
}


void displays(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (GLdouble)sww, 0.0, (GLdouble)swh, -1.0-zoom, 3.5);
    DisplayBodies();
    glutSwapBuffers();
}

void refresh(void)
{
    glutSetWindow(staticS);
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
            zoom += 0.5;
            break;
        case 'Z':
            zoom -= 0.5;
            break;
    }
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    read_info("input/256info");
    read_input("input/256init");
    read_results("input/256result");
}

