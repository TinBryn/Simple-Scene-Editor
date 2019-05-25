//
// Created by kieran on 24/05/19.
//

#include <scene_object.h>
#include <state.h>
#include "math3d/mat.h"

SceneObject::SceneObject(int model, int texture)
        : location{}, color{1}, scale{1}, angles{},
          modelId{model}, textureId{texture}, texScale{1}, shininess{5}, metalicity{0.5}
{

}

SceneObject::SceneObject(int model, int texture, Vec3 location, float scale)
        : location{location}, color{1}, scale{scale}, angles{},
        modelId{model}, textureId{texture}, texScale{1}, shininess{5}, metalicity{0.5}
{

}

void addObject(int id)
{
    Vec2 screenMiddle = Vec2(State::window_width / 2.0, State::window_height / 2.0);
    float scale = State::camera.distance / 150.0;

    Vec2 currPosT = Mat2(1)
            .rotated(-State::camera.hAngle)
            .scaled(scale, scale)
            * (State::mouse.pos - screenMiddle);


    Vec3 currPos = Vec3(currPosT.x, 10, -currPosT.y);

    std::uniform_int_distribution<int> textureSelect(2, 30);
    State::objects.emplace_back(id, textureSelect(State::randomEngine), currPos, 1.0);
    State::currObject = State::objects.size()-1;

}