//
// Created by kieran on 22/05/19.
//

#include <state.h>
#include <GL/glut.h>
#include "callbacks.h"

void idle()
{
    if (State::mouse.pressed[1])
    {
        Vec2 delta = State::mouse.delta;


        State::camera.hAngle -= delta.x / 100.0;
        State::camera.vAngle -= delta.y / 100.0;
    }

    if (State::mouse.pressed[0])
    {
        State::camera.distance -= State::mouse.delta.y / 10.0;
    }

    State::mouse.delta = {};

    glutPostRedisplay();
}