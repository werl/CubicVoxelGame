//
// Created by Peter Lewis on 2017-11-14.
//
#include "mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <spdlog/spdlog.h>

/**
 * Constructor loading the specified mesh
 *
 * @param mesh - mesh to load
 */
Mesh::MeshEntry::MeshEntry(aiMesh *mesh, aiMaterial *material, gl::GLuint program) {
    gl::glGenVertexArrays(1, &vao);
    gl::glBindVertexArray(vao);

    elementCount = mesh->mNumFaces * 3;

    if(mesh->HasPositions()) {
        auto *vertices = new float[mesh->mNumVertices * 3];

        for(int i = 0; i < mesh->mNumVertices; i++) {
            vertices[i * 3] = mesh->mVertices[i].x;
            vertices[i * 3 + 1] = mesh->mVertices[i].y;
            vertices[i * 3 + 2] = mesh->mVertices[i].z;
        }

        gl::glGenBuffers(1, &vbo[VERTEX_BUFFER]);
        gl::glBindBuffer(gl::GL_ARRAY_BUFFER, vbo[VERTEX_BUFFER]);
        gl::glBufferData(gl::GL_ARRAY_BUFFER, 3 * mesh->mNumVertices * sizeof(gl::GLfloat), vertices, gl::GL_STATIC_DRAW);

        gl::glVertexAttribPointer(0, 3, gl::GL_FLOAT, gl::GL_FALSE, 0, NULL);
        gl::glEnableVertexAttribArray(0);

        delete[] vertices;
    } if(mesh->HasTextureCoords(0)) {
        auto *texCoords = new float[mesh->mNumVertices * 2];

        for(int i = 0; i < mesh->mNumVertices; i++) {
            texCoords[i * 2] = mesh->mTextureCoords[0][i].x;
            texCoords[i * 2 + 1] = mesh->mTextureCoords[0][i].y;
        }

        gl::glGenBuffers(1, &vbo[TEXCOORD_BUFFER]);
        gl::glBindBuffer(gl::GL_ARRAY_BUFFER, vbo[TEXCOORD_BUFFER]);
        gl::glBufferData(gl::GL_ARRAY_BUFFER, 2 * mesh->mNumVertices * sizeof(gl::GLfloat), texCoords, gl::GL_STATIC_DRAW);

        gl::glVertexAttribPointer(1, 3, gl::GL_FLOAT, gl::GL_FALSE, 0, NULL);
        gl::glEnableVertexAttribArray(1);

        delete[] texCoords;
    } if(mesh->HasNormals()) {
        auto *normals = new float[mesh->mNumVertices * 3];

        for(int i = 0; i < mesh->mNumVertices; i++) {
            normals[i * 3] = mesh->mNormals[i].x;
            normals[i * 3 + 1] = mesh->mNormals[i].y;
            normals[i * 3 + 2] = mesh->mNormals[i].z;
        }

        gl::glGenBuffers(1, &vbo[NORMAL_BUFFER]);
        gl::glBindBuffer(gl::GL_ARRAY_BUFFER, vbo[NORMAL_BUFFER]);
        gl::glBufferData(gl::GL_ARRAY_BUFFER, 3 * mesh->mNumVertices * sizeof(gl::GLfloat), normals, gl::GL_STATIC_DRAW);

        gl::glVertexAttribPointer(2, 3, gl::GL_FLOAT, gl::GL_FALSE, 0, NULL);
        gl::glEnableVertexAttribArray(2);

        delete[] normals;
    } if(mesh->HasFaces()) {
        auto *indices = new unsigned int[mesh->mNumFaces * 3];

        for(int i = 0; i < mesh->mNumFaces; i++) {
            indices[i * 3] = mesh->mFaces[i].mIndices[0];
            indices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
            indices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
        }

        gl::glGenBuffers(1, &vbo[INDEX_BUFFER]);
        gl::glBindBuffer(gl::GL_ELEMENT_ARRAY_BUFFER, vbo[INDEX_BUFFER]);
        gl::glBufferData(gl::GL_ELEMENT_ARRAY_BUFFER, 3 * mesh->mNumFaces * sizeof(gl::GLuint), indices, gl::GL_STATIC_DRAW);

        gl::glVertexAttribPointer(3, 3, gl::GL_FLOAT, gl::GL_FALSE, 0, NULL);
        gl::glEnableVertexAttribArray(3);

        delete[] indices;
    }

    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, 0);
    gl::glBindVertexArray(0);

    aiColor3D color(1, 0.4, 0);

    if(AI_SUCCESS != material->Get(AI_MATKEY_COLOR_DIFFUSE, color)) {
        spdlog::get("console")->error("Material not found");
    }
    red = color.r;
    green = color.g;
    blue = color.b;
    this->program = program;


}

Mesh::MeshEntry::~MeshEntry() {
    if(vbo[VERTEX_BUFFER])
        gl::glDeleteBuffers(1, &vbo[VERTEX_BUFFER]);
    if(vbo[TEXCOORD_BUFFER])
        gl::glDeleteBuffers(1, &vbo[TEXCOORD_BUFFER]);
    if(vbo[NORMAL_BUFFER])
        gl::glDeleteBuffers(1, &vbo[NORMAL_BUFFER]);
    if(vbo[INDEX_BUFFER])
        gl::glDeleteBuffers(1, &vbo[INDEX_BUFFER]);

    gl::glDeleteVertexArrays(1, &vao);
}

/**
 * Render a single Mesh Entry
 */
void Mesh::MeshEntry::render(glm::vec3 position) {
    gl::GLint color = gl::glGetUniformLocation(program, "fragColor");
    gl::glUniform3f(color, red, green, blue);

    gl::GLint pos = gl::glGetUniformLocation(program, "position");
    position *= 3;
    gl::glUniform3f(pos, position.x, position.y, position.z);

    gl::glBindVertexArray(vao);
    gl::glDrawElements(gl::GL_TRIANGLES, elementCount, gl::GL_UNSIGNED_INT, nullptr);
    gl::glBindVertexArray(0);
}

/**
 * Constructor, just put in the path and file you want to load
 *
 * @param filePath - path to the file to load
 */
Mesh::Mesh(std::string filePath, gl::GLuint program, glm::vec3 position) {
    this->position = position;

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filePath.c_str(), aiProcessPreset_TargetRealtime_Fast);

    if(!scene) {
        fprintf(stderr, "unable to load mesh %s\n", importer.GetErrorString());
    }

    for(int i = 0; i < scene->mNumMeshes; i++) {
        meshEntries.push_back(new MeshEntry(scene->mMeshes[i], scene->mMaterials[scene->mMeshes[i]->mMaterialIndex], program));
    }
}

Mesh::~Mesh() {
    for(int i = 0; i < meshEntries.size(); i++) {
        delete meshEntries.at(i);
    }

    meshEntries.clear();
}

/**
 * render the whole mesh
 */
void Mesh::render() {
    for(int i = 0; i < meshEntries.size(); i++) {
        meshEntries.at(i)->render(position);
    }
}