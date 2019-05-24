//
// Created by kieran on 23/05/19.
//

#ifndef CITS3003_CAMERA_H
#define CITS3003_CAMERA_H

#include <math3d/vec.h>

struct Camera
{
    Vec3 position;
    float hAngle;
    float vAngle;
    float zoom;
    float distance;
};

#endif //CITS3003_CAMERA_H
