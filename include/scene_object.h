//
// Created by kieran on 23/05/19.
//

#ifndef CITS3003_SCENE_OBJECT_H
#define CITS3003_SCENE_OBJECT_H

#include <math3d/vec.h>

struct SceneObject
{
    SceneObject(int model, int texture);
    SceneObject(int model, int texture, Vec3 location, float scale);
    SceneObject() = default;

    Vec3 location;
    Vec3 color;
    float scale;
    float angles[3];
    int modelId;
    int textureId;
    float texScale;
    float shininess;
    float metalicity;
};

void addObject(int id);

#endif //CITS3003_SCENE_OBJECT_H
