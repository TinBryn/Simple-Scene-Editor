//
// Created by kieran on 22/05/19.
//

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <state.h>
#include <iostream>
#include <math3d/mat.h>
#include "callbacks.h"


void render_scene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(Model model : State::models)
    {
        Mat4 modelView = Mat4(1)
                .rotatedZX(State::angle)
                .translated(0.0, -50, 0.0)
                .scaled(0.01);
        glUniformMatrix4fv(State::program.ModelView_location, 1, GL_FALSE, modelView.data);
        model.render();
    }
    glutSwapBuffers();
}