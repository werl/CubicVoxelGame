//
// Created by Peter Lewis on 2017-11-20.
//

#include "mesh_manager.hpp"
#include <spdlog/spdlog.h>

std::map<std::string, Mesh*>* mesh::MeshManager::getMeshMap() {
    static auto meshes = new std::map<std::string, Mesh*>();
    return meshes;
}

void mesh::MeshManager::registerMesh(Mesh &mesh, std::string meshName) {
    std::shared_ptr<spdlog::logger> console = spdlog::get("console");

    auto meshes = mesh::MeshManager::getMeshMap();

    auto found = meshes->find(meshName);

    if(found != meshes->end()) {
        console->critical("Duplicate mesh name registration was attempted: \"{}\"", meshName);
        return;
    }
    meshes->insert(std::pair<std::string, Mesh*>(meshName, &mesh));
    console->info("Successfully register mesh \"{}\"", meshName);
}

Mesh* mesh::MeshManager::getMesh(std::string meshName) {
    auto meshes = mesh::MeshManager::getMeshMap();
    try {
        Mesh *ret = meshes->at(meshName);
        return ret;
    } catch(const std::out_of_range &err) {
        spdlog::get("console")->error("{}", err.what());
        return nullptr;
    }
}
