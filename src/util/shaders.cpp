//
// Created by kieran on 23/05/19.
//

#include <fstream>
#include <GL/glew.h>
#include <util/shaders.h>
#include <stdexcept>
#include <vector>

std::string load_stream(std::istream &stream)
{
    if (!stream)
    {
        throw std::runtime_error("input is not available");
    }
    return {std::istreambuf_iterator<char>(stream), {}};
}

void Shader::compile()
{
    std::ifstream file(filename);
    std::string source = load_stream(file);
    id = glCreateShader(type);
    const char *c_source = source.c_str();
    glShaderSource(id, 1, &c_source, nullptr);
    glCompileShader(id);
    int status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> log(length);
        glGetShaderInfoLog(id, length, nullptr, &log[0]);
        std::string msg = &log[0];
        throw std::runtime_error(msg + source);
    }
}

void Shader::destroy()
{
    if (id != 0)
    {
        glDeleteShader(id);
        id = 0;
    }
}

void ShaderProgram::attachShader(Shader const &shader)
{
    shaders.push_back(shader);
}

void ShaderProgram::link()
{
    glLinkProgram(id);
    int status;
    glGetProgramiv(id, GL_LINK_STATUS, &status);
    if (!status)
    {
        int length;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> log(length);
        glGetProgramInfoLog(id, length, nullptr, &log[0]);
        std::string msg = &log[0];
        throw std::runtime_error(msg);
    }
}

void ShaderProgram::reload()
{
    glUseProgram(0);
    glDeleteProgram(id);
    id = glCreateProgram();
    for (auto &shader : shaders)
    {
        shader.compile();
        glAttachShader(id, shader.id);
    }

    link();

    for (auto &shader: shaders)
    {
        glDetachShader(id, shader.id);
        shader.destroy();
    }

    glUseProgram(id);

    vPosition_location = glGetAttribLocation(id, "vPosition");
    vTex_location = glGetAttribLocation(id, "vTex");
    vNormal_location = glGetAttribLocation(id, "vNormal");
    ModelView_location = glGetUniformLocation(id, "ModelView");
}
