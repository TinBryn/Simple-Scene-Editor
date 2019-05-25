//
// Created by kieran on 22/05/19.
//

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <state.h>
#include <iostream>
#include <math3d/mat.h>
#include "callbacks.h"

//Lazily initialize textures and models
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

void drawObject(SceneObject const &object)
{
    Mat4 Model = Mat4(1)
            .rotatedYZ(object.angles[0])
            .rotatedXY(object.angles[2])
            .rotatedZX(object.angles[1])

            .scaled(object.scale)
            .translated(object.location);

    glUniformMatrix4fv(State::program.Model_location, 1, GL_TRUE, Model.data);

    glActiveTexture(GL_TEXTURE0);

    unsigned int tID = getTexture(object.textureId).id;
    glBindTexture(GL_TEXTURE_2D, tID);

    glUniform1i(State::program.texture_location, 0);
    glUniform1f(State::program.shininess_location, object.shininess);
    glUniform1f(State::program.textureScale_location, object.texScale);
    glUniform1f(State::program.metalicity_location, object.metalicity);
    glUniform3fv(State::program.objectColor_location, 1, object.color.data());
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
    //view Matrix
    glUniformMatrix4fv(State::program.View_location, 1, GL_TRUE, view.data);

    float m = std::min(State::window_width, State::window_height) * State::camera.zoom;

    Mat4 projection = perspective(State::window_width / m, State::window_height / m, 0.1, 10000);
    //projection Matrix
    glUniformMatrix4fv(State::program.Projection_location, 1, GL_TRUE, projection.data);

    glUniform3fv(State::program.LightPosition1_location, 1, State::light1.rep.location.data());
    glUniform3fv(State::program.LightColor1_location, 1, State::light1.color.data());

    glUniform3fv(State::program.LightPosition2_location, 1, State::light2.rep.location.data());
    glUniform3fv(State::program.LightColor2_location, 1, State::light2.color.data());

    glUniform3fv(State::program.Ambient_location, 1, State::ambientColor.data());

    drawObject(State::floor);
    drawObject(State::light1.rep);
    drawObject(State::light2.rep);


    for (SceneObject object : State::objects)
    {
        drawObject(object);
    }
    glutSwapBuffers();
}