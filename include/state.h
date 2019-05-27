//
// Created by kieran on 22/05/19.
//

#ifndef CITS3003_STATE_H
#define CITS3003_STATE_H

//global state is stored here

#include <vector>
#include <random>
#include <util/shaders.h>
#include <assimp/scene.h>
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
    static int const numMeshes;
    static int const numTextures;
    static int currObject;
    static int currMode;
    static ShaderProgram program;
    static std::vector<Model> models;
    static std::vector<texture> textures;
    static Camera camera;
    static Mouse mouse;
    static std::vector<SceneObject> objects;
    static SceneObject floor;
    static Light light1;
    static Light light2;
    static std::default_random_engine randomEngine;
    static Vec3 ambientColor;
    static float fogDistance;
    static Vec3 fogColor;
    static std::vector<aiScene const*> scenes;
    static int numberFrames;
};

#endif //CITS3003_STATE_H
