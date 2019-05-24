//
// Created by kieran on 22/05/19.
//

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <state.h>
#include <iostream>
#include <math3d/mat.h>
#include "callbacks.h"

texture &getTexture(int i)
{
    texture &t = State::textures[i];
    if (t.rgbData == nullptr)
    {
        t = texture::openFromFile("../models-textures/texture" + std::to_string(i) + ".bmp");
    }
    return t;
}

Model &getModel(int i)
{
    Model &m = State::models[i];
    if (m.vao == 0)
    {
        m = Model::initFromFile("../models-textures/model" + std::to_string(i) + ".x", State::program);
    }
    return m;
}

void drawObject(SceneObject const &object, Mat4 const &View)
{
    Mat4 modelView = View * Mat4(1)
            .rotatedYZ(object.angles[0])
            .rotatedZX(object.angles[1])
            .rotatedXY(object.angles[2])
            .scaled(object.scale)
            .translated(object.location);

    glUniformMatrix4fv(State::program.ModelView_location, 1, GL_TRUE, modelView.data);

    glActiveTexture(GL_TEXTURE0);

    unsigned int tID = getTexture(object.textureId).id;
    glBindTexture(GL_TEXTURE_2D, tID);

    glUniform1i(State::program.texture_location, 0);
    glBindVertexArray(getModel(object.modelId).vao);

    glDrawElements(GL_TRIANGLES, State::models[object.modelId].size, GL_UNSIGNED_INT, nullptr);
}

void render_scene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Mat4 view = Mat4(1)
            .translated(-State::camera.position)
            .rotatedZX(State::camera.hAngle)
            .rotatedYZ(State::camera.vAngle)
            .translated(0.0, 0.0, State::camera.distance)

    ;

    float m = std::min(State::window_width, State::window_height) * State::camera.zoom;

    Mat4 projection = perspective(State::window_width / m, State::window_height / m, 0.1, 1000);

    glUniformMatrix4fv(State::program.Projection_location, 1, GL_TRUE, projection.data);

    drawObject(State::floor, view);

    for (SceneObject object : State::objects)
    {
        drawObject(object, view);
    }
    glutSwapBuffers();
}