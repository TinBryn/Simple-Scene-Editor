//
// Created by kieran on 23/05/19.
//

#ifndef CITS3003_MODEL_H
#define CITS3003_MODEL_H

#include <string>
#include <util/shaders.h>
#include <array>
#include "math3d/mat.h"

struct Model
{
    unsigned int vao;
    unsigned int size;
    aiMesh const* mesh;
    std::vector<std::array<float, 4>> boneIds;
    std::vector<std::array<float, 4>> boneWeights;
    std::vector<Mat4> boneTransforms;
    static Model setupModel(aiMesh const * mesh, ShaderProgram const &program);
    static Model initFromFile(std::string const &filename, ShaderProgram const &program);
    static Model initFromScene(aiScene const*scene, ShaderProgram const &program);
    static aiScene const* loadScene(std::string const &filename);
};

#endif //CITS3003_MODEL_H
