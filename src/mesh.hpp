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
private:
    std::string filePath;



public:
    struct MeshEntry {
        static enum Buffers {
            VERTEX_BUFFER, TEXCOORD_BUFFER, NORMAL_BUFFER, INDEX_BUFFER
        };

        gl::GLuint vao;
        gl::GLuint vbo[4];

        unsigned int elementCount;

        explicit MeshEntry(aiMesh *mesh);
        ~MeshEntry();

        void load(aiMesh *mesh);
        void render();
    };

    explicit Mesh(std::string filePath);

    void render();

    ~Mesh();

private:
    std::vector<MeshEntry*> meshEntries;
};


#endif //TRANSPORTCONCEPT2D_MESH_HPP
