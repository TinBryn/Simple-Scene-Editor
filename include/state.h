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
#include "mouse.h"
#include "light.h"

struct State
{
    static int window_width;
    static int window_height;
    static ShaderProgram program;
    static std::vector<Model> models;
    static std::vector<texture> textures;
    static Camera camera;
    static Mouse mouse;
    static std::vector<SceneObject> objects;
    static SceneObject floor;
    static Light light;
};

#endif //CITS3003_STATE_H
