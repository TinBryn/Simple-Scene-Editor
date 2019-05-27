//
// Created by kieran on 26/05/19.
//

#include <string>
#include <state.h>
#include <GL/glut.h>
#include "callbacks.h"

void timer(int)
{
    static int last_time = State::numberFrames;
    std::string title = "Frames per second: " + std::to_string(State::numberFrames - last_time);
    glutSetWindowTitle(title.c_str());

    last_time = State::numberFrames;

    glutTimerFunc(1000, timer, 1);
}