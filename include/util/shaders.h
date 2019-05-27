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
    using loc = unsigned int;
    unsigned int id;
    void attachShader(Shader const&shader);
    void reload();
    void link();
    loc vPosition_location;
    loc vTex_location;
    loc vNormal_location;
    loc Model_location;
    loc View_location;
    loc texture_location;
    loc Projection_location;
    loc Ambient_location;

    loc LightPosition1_location;
    loc LightColor1_location;
    loc LightPosition2_location;
    loc LightColor2_location;

    loc shininess_location;
    loc objectColor_location;
    loc textureScale_location;
    loc metalicity_location;
    loc fogDistance_location;
    loc fogColor_location;
    loc boneIDs_location;
    loc boneWeights_location;
    loc boneTransforms_location;

private:
    std::vector<Shader> shaders;
};

#endif //CITS3003_SHADERS_H
