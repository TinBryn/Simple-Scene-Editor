//
// Created by kieran on 22/05/19.
//

#include "state.h"

int State::window_width;
int State::window_height;
ShaderProgram State::program;
std::vector<texture> State::textures;
std::vector<Model> State::models;
Camera State::camera{{0,0,-150}, 0, -0.2, 1};
std::vector<SceneObject> State::objects;
SceneObject State::floor;
int State::mouseX;
int State::mouseY;
int State::mouseButton;
Vec3 State::lightPos;
Vec3 State::lightColor;