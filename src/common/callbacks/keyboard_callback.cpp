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
            glutPostRedisplay();
            std::cout << "done" << std::endl;

            break;
        case 'w':
            State::camera.position.y += 10;
            break;
        case 's':
            State::camera.position.y -= 10;
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
        case GLUT_KEY_LEFT:
            break;
        case GLUT_KEY_RIGHT:
            break;
        default:
            std::cout << key << std::endl;
            break;
    }
}