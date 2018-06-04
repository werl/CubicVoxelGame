//
// Created by Peter Lewis on 2017-11-14.
//

#ifndef CUBICVOXELGAME_MESH_HPP
#define CUBICVOXELGAME_MESH_HPP

#include <string>
#include <vector>

#include <glbinding/gl41/gl.h>

#include <glm/glm.hpp>

#include <assimp/scene.h>
#include <assimp/mesh.h>

class Mesh {
public:
    struct MeshEntry {
        enum Buffers {
            VERTEX_BUFFER, TEXCOORD_BUFFER, NORMAL_BUFFER, INDEX_BUFFER
        };

        gl::GLuint vao;
        gl::GLuint vbo[4];
        gl::GLuint program;
        float red;
        float green;
        float blue;

        unsigned int elementCount;

        MeshEntry(aiMesh *mesh, aiMaterial *material);
        MeshEntry(const MeshEntry &obj);
        ~MeshEntry();

        void render(glm::vec3 *position, gl::GLuint program);
    };

private:
    std::vector<MeshEntry*> meshEntries;
public:
    explicit Mesh(std::string filePath);
    Mesh(const Mesh &obj);
    ~Mesh();

    void render(glm::vec3 *pos, gl::GLuint program);

};

#endif //CUBICVOXELGAME_MESH_HPP
