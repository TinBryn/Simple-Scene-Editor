//
// Created by kieran on 22/05/19.
//

#include <state.h>
#include <cmath>
#include <GL/glut.h>
#include <iostream>
#include "callbacks.h"
#include "math3d/mat.h"

float brightness(Vec3 color)
{
    return color.x + color.y + color.z;
}

Vec3 colorShift(Vec3 color, float orange, float green, float lum, float minLux, float maxLux)
{
    float y = (color.x + color.y * 2 + color.z) * 0.25;
    float co = (color.x - color.z) * 0.5;
    float cg = (2 * color.y - color.x - color.z) * 0.25;

    float yfactor = (std::min(std::max(y + lum, minLux), maxLux)) / y;

    co *= yfactor;
    cg *= yfactor;
    orange *= yfactor;
    green *= yfactor;
    y *= yfactor;

    co = std::min(std::max(co + orange, -y), y);
    cg = std::min(std::max(cg + green, -y), y);

    return {y + co - cg, y + cg, y - co - cg};
}

void idle()
{
    Vec2 delta = State::mouse.delta;
    Vec2 rotatedDelta = Mat2(1).rotated(-State::camera.hAngle) * delta;
    if (State::mouse.pressed[1])
    {

        switch (State::currMode)
        {
            case 50:
                State::camera.hAngle -= delta.x / 100.0;
                State::camera.vAngle -= delta.y / 100.0;
                break;
            case 55:
            {
                SceneObject &curr = State::objects[State::currObject];
                curr.angles[0] += delta.x / 100;
                curr.angles[2] -= delta.y / 100;
            }
                break;
            case 41:
                State::objects[State::currObject].location.x += rotatedDelta.x / 1;
                State::objects[State::currObject].location.z -= rotatedDelta.y / 1;
                break;
            case 70:
                State::light1.rep.location.x += rotatedDelta.x;
                State::light1.rep.location.z -= rotatedDelta.y;
                break;
            case 71:
                State::light1.color = colorShift(State::light1.color, delta.y * -0.25, delta.x * 0.25, 0, 0, 500);
                break;
            case 80:
                State::light2.rep.location.x += rotatedDelta.x;
                State::light2.rep.location.z -= rotatedDelta.y;
                break;
            case 81:
                State::light2.color = colorShift(State::light2.color, delta.y * -0.25, delta.x * 0.25, 0, 0, 500);
                break;
            case 10:
                State::objects[State::currObject].color = colorShift(State::objects[State::currObject].color,
                                                                     delta.y * -0.025, delta.x * 0.025, 0, 0.1, 1);
                break;
            case 20:
                State::ambientColor = colorShift(State::ambientColor, delta.y * -0.025, delta.x * 0.025, 0, 0, 1);
                break;
            case 21:
                State::objects[State::currObject].shininess = std::min(std::max(State::objects[State::currObject].shininess - 0.02f * delta.y, 0.0f), 5.0f);
                State::objects[State::currObject].metalicity = std::min(std::max(State::objects[State::currObject].metalicity + 0.02f * delta.x, 0.0f), 1.0f);
                std::cout << "shininess" << State::objects[State::currObject].shininess << std::endl;
                break;
            default:
                break;
        }
    }

    if (State::mouse.pressed[0])
    {
        switch (State::currMode)
        {
            case 50:
                State::camera.distance -= delta.y / 10.0;
                break;
            case 41:
                State::objects[State::currObject].scale *= (1 - 0.03 * delta.y);
                break;
            case 55:
            {
                SceneObject &curr = State::objects[State::currObject];
                curr.angles[1] -= delta.x / 100;
            }
                break;
            case 70:
                State::light1.rep.location.y -= delta.y;
                break;
            case 71:
                State::light1.color = colorShift(State::light1.color, 0, 0, delta.y * -0.1, 0.1, 500);
                break;
            case 80:
                State::light2.rep.location.y -= delta.y;
                break;
            case 81:
                State::light2.color = colorShift(State::light2.color, 0, 0, delta.y * -0.1, 0.1, 500);
                break;
            case 10:
                State::objects[State::currObject].color = colorShift(State::objects[State::currObject].color, 0, 0,
                                                                     delta.y * -0.01, 0.1, 1);
                break;
            case 56:
                State::objects[State::currObject].texScale *= (1 - 0.03 * delta.y);

            default:
                break;
        }
    }

    State::mouse.delta = {};

    glutPostRedisplay();
}