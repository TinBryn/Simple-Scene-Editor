//
// Created by kieran on 22/05/19.
//

#include <string>
#include <iterator>
#include <GL/glew.h>
#include "shader_init.h"

std::string load_stream(std::istream &stream)
{
    return {std::istreambuf_iterator<char>(stream), {}};
}

unsigned int compileShader(std::string const &source, GLenum type)
{
    unsigned int id = glCreateShader(type);
    const char *c_source = source.c_str();
    glShaderSource(id, 1, &c_source, nullptr);
    glCompileShader(id);
    int status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        exit(EXIT_FAILURE);
    }
    return id;
}

void linkProgram(unsigned int id)
{
    glLinkProgram(id);
    int status;
    glGetProgramiv(id, GL_LINK_STATUS, &status);
    if (!status)
    {
        exit(EXIT_FAILURE);
    }
}

unsigned int initShader(std::istream &vert, std::istream &frag)
{
    unsigned int v = compileShader(load_stream(vert), GL_VERTEX_SHADER);
    unsigned int f = compileShader(load_stream(frag), GL_FRAGMENT_SHADER);

    unsigned int id = glCreateProgram();
    glAttachShader(id, v);
    glAttachShader(id, f);
    linkProgram(id);
    return id;
}
