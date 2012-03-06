#include "extra.hpp"

int main(int argc, char** argv)
{

    init_var();
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(sww, swh); // window size
    glutInitWindowPosition (0, 0); // window position on screen
    window_id=glutCreateWindow("Bodies");

    init();
    glutDisplayFunc(displays);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keys);
    glutMouseFunc(mouse);
    glutMotionFunc (mouse_motion);
    glutIdleFunc(refresh);
    glutMainLoop();
}
