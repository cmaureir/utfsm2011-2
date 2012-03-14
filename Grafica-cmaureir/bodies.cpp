#include "extra.hpp"

int main(int argc, char** argv)
{
    cout << "Loading files..." << endl;
    init_var();
    read_files();
    cout << "[READY], press any key to continue" << endl;
    getchar();

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(sww, swh); // window size
    glutInitWindowPosition (0, 0); // window position on screen
    window_id=glutCreateWindow("Bodies");
    glutSetCursor(GLUT_CURSOR_NONE);

    init();
    glutDisplayFunc(refresh);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keys);
    glutMouseFunc(mouse);
    glutMotionFunc (mouse_motion);
    glutIdleFunc(refresh);
    glutMainLoop();
}
