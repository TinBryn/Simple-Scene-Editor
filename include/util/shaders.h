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
    unsigned int Model_location;
    unsigned int View_location;
    unsigned int texture_location;
    unsigned int Projection_location;
    unsigned int Ambient_location;

    unsigned int LightPosition1_location;
    unsigned int LightColor1_location;
    unsigned int LightPosition2_location;
    unsigned int LightColor2_location;

    unsigned int shininess_location;
    unsigned int objectColor_location;
    unsigned int textureScale_location;
    unsigned int metalicity_location;

private:
    std::vector<Shader> shaders;
};

#endif //CITS3003_SHADERS_H
