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
    unsigned int texture_location;
    unsigned int Projection_location;
    unsigned int Ambient_location;
    unsigned int Diffuse_location;
    unsigned int Specular_location;
    unsigned int LightPosition_location;
    unsigned int LightColor_location;
    unsigned int Shininess_location;

private:
    std::vector<Shader> shaders;
};

#endif //CITS3003_SHADERS_H
