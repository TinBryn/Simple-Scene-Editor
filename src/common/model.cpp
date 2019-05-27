//
// Created by kieran on 23/05/19.
//

#include <GL/glew.h>
#include <math3d/vec.h>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include "model.h"

void
getBonesAffectingEachVertex(aiMesh const *mesh, std::vector<std::array<float, 4>> &boneIds,
                            std::vector<std::array<float, 4>> &boneWeights)
{
    int nVertices = mesh->mNumVertices;

    boneWeights = std::vector<std::array<float, 4>>(nVertices);
    boneIds = std::vector<std::array<float, 4>>(nVertices);

    int nBones = mesh->mNumBones;

    if (nBones == 0)
    {
        for (int i = 0; i < nVertices; i++)
        {
            boneIds[i][0] = 0;
            boneIds[i][1] = 0;
            boneIds[i][2] = 0;
            boneIds[i][3] = 0;

            boneWeights[i][0] = 1.0;
            boneWeights[i][1] = 1.0;
            boneWeights[i][2] = 1.0;
            boneWeights[i][3] = 1.0;
        }
        return;
    }

    aiBone **bones = mesh->mBones;

    for (int boneId = 0; boneId < nBones; boneId++)
    {
        for (int weightId = 0; weightId < bones[boneId]->mNumWeights; weightId++)
        {
            int vertexId = bones[boneId]->mWeights[weightId].mVertexId;
            float weight = bones[boneId]->mWeights[weightId].mWeight;

            for (int slotId = 0; slotId < 4; slotId++)
            {
                if (boneWeights[vertexId][slotId] < weight)
                {
                    for (int shuf = 3; shuf > slotId; shuf--)
                    {
                        boneWeights[vertexId][shuf] = boneWeights[vertexId][shuf - 1];
                        boneIds[vertexId][shuf] = boneIds[vertexId][shuf - 1];
                    }
                    boneWeights[vertexId][slotId] = weight;
                    boneIds[vertexId][slotId] = boneId;
                    break;
                }
            }
        }
    }
}

aiMesh *loadMesh(const std::string &filename)
{
    aiScene const *scene = aiImportFile(filename.c_str(),
                                        aiProcessPreset_TargetRealtime_Quality | aiProcess_ConvertToLeftHanded);
    return scene->mMeshes[0];
}

Model Model::initFromFile(std::string const &filename, ShaderProgram const &program)
{
    aiMesh const *mesh = loadMesh(filename);

    return setupModel(mesh, program);
}

aiScene const *Model::loadScene(std::string const &filename)
{
    return aiImportFile(filename.c_str(), aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_ConvertToLeftHanded);
}

Model Model::setupModel(aiMesh const *mesh, ShaderProgram const &program)
{
    GLuint buffers[4];
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(4, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);

    int nVerts = mesh->mNumVertices;
    long scaleVertex = sizeof(float) * 3;

    Model model;
    model.vao = vao;
    model.mesh = mesh;
    model.size = mesh->mNumFaces * 3;

    getBonesAffectingEachVertex(mesh, model.boneIds, model.boneWeights);

    GLuint elements[mesh->mNumFaces * 3];
    for (GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        elements[i * 3] = mesh->mFaces[i].mIndices[0];
        elements[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
        elements[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
    }

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (3 + 3 + 3) * nVerts, nullptr,
                 GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, scaleVertex * nVerts, mesh->mVertices);
    glBufferSubData(GL_ARRAY_BUFFER, scaleVertex * nVerts, scaleVertex * nVerts, mesh->mTextureCoords[0]);
    glBufferSubData(GL_ARRAY_BUFFER, 2 * scaleVertex * nVerts, scaleVertex * nVerts, mesh->mNormals);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);


#define BUFFER_OFFSET(x) (void*) (x)

    glVertexAttribPointer(program.vPosition_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(program.vPosition_location);

    glVertexAttribPointer(program.vTex_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(scaleVertex * nVerts));
    glEnableVertexAttribArray(program.vTex_location);

    glVertexAttribPointer(program.vNormal_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(2 * scaleVertex * nVerts));
    glEnableVertexAttribArray(program.vNormal_location);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * nVerts, model.boneIds[0].data(), GL_STATIC_DRAW);

    glVertexAttribPointer(program.boneIDs_location, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(program.boneIDs_location);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * nVerts, model.boneWeights[0].data(), GL_STATIC_DRAW);

    glVertexAttribPointer(program.boneWeights_location, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(program.boneWeights_location);


    return model;
}

Model Model::initFromScene(aiScene const *scene, ShaderProgram const &program)
{
    return setupModel(scene->mMeshes[0], program);
}

