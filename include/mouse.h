//
// Created by kieran on 24/05/19.
//

#ifndef CITS3003_MOUSE_H
#define CITS3003_MOUSE_H

#include <math3d/vec.h>

struct Mouse
{
    Vec2 pos;
    Vec2 delta;
    bool pressed[2];

};

#endif //CITS3003_MOUSE_H
