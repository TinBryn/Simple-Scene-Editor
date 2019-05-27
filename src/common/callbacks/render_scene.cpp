//
// Created by kieran on 22/05/19.
//

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <assimp/cimport.h>
#include <state.h>
#include <iostream>
#include <math3d/mat.h>
#include "callbacks.h"
#include "model.h"

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
        aiScene const *scene = Model::loadScene("../models-textures/model" + std::to_string(i) + ".x");
        State::scenes[i] = scene;
        m = Model::initFromScene(scene, State::program);
    }
    return m;
}

void calculateAnimPose(aiMesh const *mesh, aiScene const *scene, int animNum, float poseTime,
                       std::vector<Mat4> &boneTransforms)
{
    if (mesh->mNumBones == 0)
    {
        boneTransforms = std::vector<Mat4>{Mat4(1)};
        return;
    }
    if (scene->mNumAnimations <= animNum)
    {
        throw std::runtime_error("No animation with number");
    }

    aiAnimation *anim = scene->mAnimations[animNum];

    for (int chanId = 0; chanId < anim->mNumChannels; chanId++)
    {
        aiNodeAnim *channel = anim->mChannels[chanId];
        aiVector3D curPosition;
        aiQuaternion curRotation;

        aiNode *targetNode = scene->mRootNode->FindNode(channel->mNodeName);

        int posIndex;
        for (posIndex = 0; posIndex + 1 < channel->mNumPositionKeys; posIndex++)
        {
            if (channel->mPositionKeys[posIndex + 1].mTime > poseTime)
            {
                break;
            }
        }

        if (posIndex + 1 == channel->mNumPositionKeys)
            curPosition = channel->mPositionKeys[posIndex].mValue;
        else
        {
            float t0 = channel->mPositionKeys[posIndex].mTime;
            float t1 = channel->mPositionKeys[posIndex + 1].mTime;
            float weight1 = (poseTime - t0) / (t1 - t0);

            curPosition = channel->mPositionKeys[posIndex].mValue * (1 - weight1) +
                          channel->mPositionKeys[posIndex + 1].mValue * weight1;
        }

        size_t rotIndex = 0;
        for (rotIndex = 0; rotIndex + 1 < channel->mNumRotationKeys; rotIndex++)
            if (channel->mRotationKeys[rotIndex + 1].mTime > poseTime)
                break;   // the next key lies in the future - so use the current key

        if (rotIndex + 1 == channel->mNumRotationKeys)
            curRotation = channel->mRotationKeys[rotIndex].mValue;
        else
        {
            float t0 = channel->mRotationKeys[rotIndex].mTime;   // Interpolate using quaternions
            float t1 = channel->mRotationKeys[rotIndex + 1].mTime;
            float weight1 = (poseTime - t0) / (t1 - t0);

            aiQuaternion::Interpolate(curRotation, channel->mRotationKeys[rotIndex].mValue,
                                      channel->mRotationKeys[rotIndex + 1].mValue, weight1);
            curRotation = curRotation.Normalize();
        }

        aiMatrix4x4 trafo = aiMatrix4x4(curRotation.GetMatrix());             // now build a rotation matrix
        trafo.a4 = curPosition.x;
        trafo.b4 = curPosition.y;
        trafo.c4 = curPosition.z; // add the translation
        targetNode->mTransformation = trafo;  // assign this transformation to the node
    }
    boneTransforms.reserve(mesh->mNumBones);
    for (unsigned int a = 0; a < mesh->mNumBones; a++)
    {
        const aiBone *bone = mesh->mBones[a];
        aiMatrix4x4 bTrans = bone->mOffsetMatrix;  // start with mesh-to-bone matrix to subtract rest pose

        // Find the bone, then loop through the nodes/bones on the path up to the root.
        for (aiNode *node = scene->mRootNode->FindNode(bone->mName); node != nullptr; node = node->mParent)
            bTrans = node->mTransformation * bTrans;   // add each bone's current relative transformation

        boneTransforms.emplace_back(bTrans.a1, bTrans.a2, bTrans.a3, bTrans.a4,
                                    bTrans.b1, bTrans.b2, bTrans.b3, bTrans.b4,
                                    bTrans.c1, bTrans.c2, bTrans.c3, bTrans.c4,
                                    bTrans.d1, bTrans.d2, bTrans.d3, bTrans.d4);   // Convert to Mat4
    }
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
    auto &m = getModel(object.modelId);

    int nBones = m.mesh->mNumBones;
    if (nBones == 0)
    {
        nBones = 1;
    }

    std::vector<Mat4> boneTransforms;
    calculateAnimPose(State::models[object.modelId].mesh, State::scenes[object.modelId], 0,
                      (State::numberFrames % 1000) / 10.0, boneTransforms);
    glUniformMatrix4fv(State::program.boneTransforms_location, nBones, GL_TRUE, boneTransforms[0].data);

    glBindVertexArray(m.vao);

    glDrawElements(GL_TRIANGLES, State::models[object.modelId].size, GL_UNSIGNED_INT, nullptr);

}

void render_scene()
{
    State::numberFrames++;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Mat4 view = Mat4(1)
            .translated(-State::camera.position)
            .rotatedZX(State::camera.hAngle)
            .rotatedYZ(State::camera.vAngle)
            .translated(0.0, 0.0, State::camera.distance);
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
    glUniform3fv(State::program.fogColor_location, 1, State::fogColor.data());
    glUniform1f(State::program.fogDistance_location, State::fogDistance);

    drawObject(State::floor);


    for (SceneObject object : State::objects)
    {
        drawObject(object);
    }

    drawObject(State::light1.rep);
    drawObject(State::light2.rep);
    glutSwapBuffers();
}