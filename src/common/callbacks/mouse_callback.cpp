//
// Created by kieran on 24/05/19.
//

#include <state.h>
#include "callbacks.h"

void mousePassiveMotion(int x, int y)
{
    State::mouseX = x;
    State::mouseY = y;
}