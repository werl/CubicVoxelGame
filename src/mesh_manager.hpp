//
// Created by Peter Lewis on 2017-11-20.
//

#ifndef TRANSPORTCONCEPT2D_MESH_MANAGER_HPP
#define TRANSPORTCONCEPT2D_MESH_MANAGER_HPP

#include <map>
#include <string>
#include "mesh.hpp"
#include "tile_base.hpp"

namespace mesh {
    class MeshManager {
    private:
    public:
        static std::map<std::string, Mesh*>* getMeshMap();
        static void registerMesh(Mesh &mesh, std::string meshName);
        static Mesh* getMesh(std::string meshName);
    };
}

#endif //TRANSPORTCONCEPT2D_MESH_MANAGER_HPP
