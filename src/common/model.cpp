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

void resetModel(Model model, unsigned int program)
{
    glBindVertexArray(model.vao);
    GLuint vPosition_location = glGetAttribLocation(program, "vPosition");

    glVertexAttribPointer(vPosition_location, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    glEnableVertexAttribArray(vPosition_location);
}

aiMesh *loadMesh(const std::string &filename)
{
    aiScene const *scene = aiImportFile(filename.c_str(),
                                        aiProcessPreset_TargetRealtime_Quality | aiProcess_ConvertToLeftHanded);
    return scene->mMeshes[0];
}

Model Model::initFromFile(std::string const &filename, ShaderProgram program)
{
    aiMesh const *mesh = loadMesh(filename);

    GLuint buffers[2];
    GLuint vbo;
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(2, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);

    int nVerts = mesh->mNumVertices;
    long scale = sizeof(float) * 3;
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (3 + 3 + 3) * nVerts, nullptr, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, scale * nVerts, mesh->mVertices);
    glBufferSubData(GL_ARRAY_BUFFER, scale * nVerts, scale * nVerts, mesh->mTextureCoords[0]);
    glBufferSubData(GL_ARRAY_BUFFER, 2 * scale * nVerts, scale * nVerts, mesh->mNormals);

    GLuint elements[mesh->mNumFaces * 3];
    for (GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        elements[i * 3] = mesh->mFaces[i].mIndices[0];
        elements[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
        elements[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    glVertexAttribPointer(program.vPosition_location, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    glEnableVertexAttribArray(program.vPosition_location);

    glVertexAttribPointer(program.vTex_location, 3, GL_FLOAT, GL_FALSE, 0, (void *) (scale * nVerts));
    glEnableVertexAttribArray(program.vTex_location);

    glVertexAttribPointer(program.vNormal_location, 3, GL_FLOAT, GL_FALSE, 0, (void *) (2 * scale * nVerts));
    glEnableVertexAttribArray(program.vNormal_location);

    return {vao, mesh->mNumFaces * 3};
}

void Model::render()
{
    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, nullptr);
}
