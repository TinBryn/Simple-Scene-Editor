//
// Created by kieran on 24/05/19.
//

#include <state.h>
#include <GL/glut.h>
#include <iostream>
#include "callbacks.h"

void mouseMove(int x, int y)
{
    Vec2 p(x, y);
    State::mouse.delta = p - State::mouse.pos;
    State::mouse.pos = Vec2(x, y);
}

void mouseClick(int button, int state, int x, int y)
{
    switch (button)
    {
        case GLUT_LEFT_BUTTON:
            State::mouse.pressed[0] = state == GLUT_DOWN;
            break;
        case GLUT_MIDDLE_BUTTON:
            State::mouse.pressed[1] = state == GLUT_DOWN;
            break;
        case 3:
        {
            float d = State::camera.distance;
            State::camera.distance = (d < 0 ? d : d * 0.8) - 0.0125;
        }
            break;
        case 4:
        {
            float d = State::camera.distance;
            State::camera.distance = (d < 0 ? d : d * 1.25) + 0.0125;
        }
            break;
        default:
            break;
    }
}