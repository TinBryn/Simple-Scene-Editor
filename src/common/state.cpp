//
// Created by kieran on 22/05/19.
//

#include "state.h"

int State::window_width;
int State::window_height;
ShaderProgram State::program;
std::vector<texture> State::textures;
std::vector<Model> State::models;
Camera State::camera = Camera{{0,0,0}, 0, -0.2, 1, 150};
std::vector<SceneObject> State::objects;
SceneObject State::floor;
Mouse State::mouse;