//
// Created by kieran on 22/05/19.
//

#ifndef CITS3003_STATE_H
#define CITS3003_STATE_H

//global state is stored here

#include <vector>
#include <util/shaders.h>
#include "model.h"
#include "texture.h"
#include "scene_object.h"
#include "camera.h"

struct State
{
    static int window_width;
    static int window_height;
    static ShaderProgram program;
    static std::vector<Model> models;
    static std::vector<texture> textures;
    static Camera camera;
    static int mouseX;
    static int mouseY;
    static int mouseButton;
    static std::vector<SceneObject> objects;
    static SceneObject floor;
    static Vec3 lightPos;
    static Vec3 lightColor;
};

#endif //CITS3003_STATE_H
