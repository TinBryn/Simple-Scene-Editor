//
// Created by kieran on 23/05/19.
//

#ifndef CITS3003_SHADERS_H
#define CITS3003_SHADERS_H

#include <string>
#include <vector>

struct Shader
{
    unsigned int type;
    std::string filename;
    unsigned int id;
    void compile();
    void destroy();
};

struct ShaderProgram
{
    unsigned int id;
    void attachShader(Shader const&shader);
    void reload();
    void link();
    unsigned int vPosition_location;
    unsigned int vTex_location;
    unsigned int vNormal_location;
    unsigned int ModelView_location;

private:
    std::vector<Shader> shaders;
};

#endif //CITS3003_SHADERS_H
