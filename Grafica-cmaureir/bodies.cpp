#include "core.hpp"

int main(int argc, char** argv)
{
    cout << "Loading files..." << endl;
    init_var();   // Variable initialization
    read_files(); // Reading information, input and results files
    cout << "[READY], press any key to continue" << endl;
    getchar();

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH); // Single buffer
    glutInitWindowSize(sww, swh);                  // Window size
    glutInitWindowPosition (0, 0);                 // Window position
    window_id=glutCreateWindow("Bodies");          // Window title

    glutSetCursor(GLUT_CURSOR_NONE);    // Disabling cursor
    init();                             // Some initialization
    glutDisplayFunc(refresh);           // Display function to draw the particles
    glutReshapeFunc(reshape);           // Particle position update
    glutKeyboardFunc(keys);             // Key functions
    glutMouseFunc(mouse);               // Mouse functions
    glutMotionFunc(mouse_motion);       // Mouse active motion function
    glutIdleFunc(refresh);              // Re-display particles
    glutMainLoop();                     // Glut loop
}
