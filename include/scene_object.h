//
// Created by kieran on 23/05/19.
//

#ifndef CITS3003_SCENE_OBJECT_H
#define CITS3003_SCENE_OBJECT_H

#include <math3d/vec.h>

struct SceneObject
{
    SceneObject(int model, int texture);
    SceneObject() = default;

    Vec3 location;
    float scale;
    float angles[3];
    float diffuse, specular, ambient;
    float shine;
    Vec3 color;
    float brightness;
    int modelId;
    int textureId;
    float texScale;
};

#endif //CITS3003_SCENE_OBJECT_H
