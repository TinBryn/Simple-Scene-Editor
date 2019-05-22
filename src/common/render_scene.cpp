//
// Created by kieran on 22/05/19.
//

#include <GL/freeglut.h>
#include "callbacks.h"


void render_scene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
}