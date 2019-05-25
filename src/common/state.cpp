//
// Created by kieran on 22/05/19.
//

#include "state.h"

int State::window_width;
int State::window_height;
ShaderProgram State::program;
std::vector<texture> State::textures;
std::vector<Model> State::models;
Camera State::camera;
std::vector<SceneObject> State::objects;
SceneObject State::floor;
Mouse State::mouse;
Light State::light1;
Light State::light2;
Vec3 State::ambientColor;

int const State::numMeshes = 56;
int const State::numTextures = 31;

int State::currObject = 0;
int State::currMode;


std::default_random_engine State::randomEngine;
