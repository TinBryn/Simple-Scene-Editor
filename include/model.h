//
// Created by kieran on 23/05/19.
//

#ifndef CITS3003_MODEL_H
#define CITS3003_MODEL_H

#include <string>
#include <util/shaders.h>

struct Model
{
    unsigned int vao;
    unsigned int size;
    static Model initFromFile(std::string const &filename, ShaderProgram program);
    static Model initFromArray(float const *pos, float const *normals, float const *tex, unsigned int nVerts, ShaderProgram program);
};

#endif //CITS3003_MODEL_H
