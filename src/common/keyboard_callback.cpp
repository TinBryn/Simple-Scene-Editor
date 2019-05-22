//
// Created by kieran on 22/05/19.
//

#include <GL/freeglut.h>
#include "callbacks.h"

void keyboard(unsigned char key, int, int)
{
    switch(key)
    {
        case '\033':
            glutLeaveMainLoop();
            break;
        default:
            break;
    }
}