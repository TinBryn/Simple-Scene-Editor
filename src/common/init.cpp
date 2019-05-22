//
// Created by kieran on 22/05/19.
//

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "init.h"
#include "state.h"
#include "callbacks.h"

void init(int argc, char **argv)
{
    State::window_height = 768;
    State::window_width = 1024;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(State::window_width, State::window_height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glewInit();
    glutDisplayFunc(render_scene);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glClearColor(0.2, 0.3, 0.4, 1.0);
    glEnable(GL_DEPTH_TEST);
}

void loop()
{
    glutMainLoop();
}
