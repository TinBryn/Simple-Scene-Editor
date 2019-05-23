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

struct State
{
    static int window_width;
    static int window_height;
    static unsigned int shader;
    static ShaderProgram program;
    static std::vector<Model> models;
    static std::vector<texture> textures;
    static float angle;
};

#endif //CITS3003_STATE_H
