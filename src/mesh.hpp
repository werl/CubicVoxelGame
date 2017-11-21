//
// Created by Peter Lewis on 2017-11-14.
//

#ifndef TRANSPORTCONCEPT2D_MESH_HPP
#define TRANSPORTCONCEPT2D_MESH_HPP

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

        MeshEntry(aiMesh *mesh, aiMaterial *material, gl::GLuint program);
        ~MeshEntry();

        void render(glm::vec3 position);
    };

private:
    glm::vec3 position;
public:
    Mesh(std::string filePath, gl::GLuint program, glm::vec3 position);

    void render();

    ~Mesh();

private:
    std::vector<MeshEntry*> meshEntries;
};

#endif //TRANSPORTCONCEPT2D_MESH_HPP
