//
// Created by kieran on 23/05/19.
//

#include <state.h>
#include <GL/gl.h>
#include "callbacks.h"

void resize(int width, int height)
{
    State::window_width = width;
    State::window_height = height;

    glViewport(0, 0, width, height);
}