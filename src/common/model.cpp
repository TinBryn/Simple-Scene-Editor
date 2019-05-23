//
// Created by kieran on 23/05/19.
//

#include <GL/glew.h>
#include <math3d/vec.h>
#include "model.h"

Model createModel(unsigned int program)
{
    //create a triangle
    Vec3 triangle[3] = {{-0.6, -0.5, 0.0},
                        {0.6,  -0.5, 0.0},
                        {0.0,  0.8,  0.0}};

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), &triangle[0].x, GL_STATIC_DRAW);

    GLuint vPosition_location = glGetAttribLocation(program, "vPosition");

    glVertexAttribPointer(vPosition_location, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    glEnableVertexAttribArray(vPosition_location);

    return {vao};
}

void resetModel(Model model, unsigned int program)
{
    glBindVertexArray(model.vao);
    GLuint vPosition_location = glGetAttribLocation(program, "vPosition");

    glVertexAttribPointer(vPosition_location, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    glEnableVertexAttribArray(vPosition_location);
}
