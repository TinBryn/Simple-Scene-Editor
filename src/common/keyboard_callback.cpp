//
// Created by kieran on 22/05/19.
//

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "state.h"
#include "callbacks.h"

void keyboard(unsigned char key, int, int)
{
    switch(key)
    {
        case '\033':
            glutLeaveMainLoop();
            break;
        case 'r':
            std::cout << "reloading shaders" << std::endl;
            State::program.reload();
            resetModel(State::models[0], State::program.id);
            glutPostRedisplay();
            std::cout << "done" << std::endl;
            break;
        default:
            std::cout << (unsigned int) key << std::endl;
            break;
    }
}

void special_keyboard(int key, int, int)
{
    switch (key)
    {
        default:
            std::cout << key << std::endl;
            break;
    }
}