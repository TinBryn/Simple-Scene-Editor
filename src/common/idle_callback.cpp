//
// Created by kieran on 22/05/19.
//

#include <state.h>
#include <GL/glut.h>
#include "callbacks.h"

void idle()
{
    State::angle += 0.01;
    glutPostRedisplay();
}