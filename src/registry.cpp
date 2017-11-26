//
// Created by Peter Lewis on 2017-11-20.
//

#include "registry.hpp"
#include <spdlog/spdlog.h>

void registerTileAndMesh(tile::TileBase &tile, Mesh &mesh, std::string registryName) {
    tile::TileBase::registerTile(tile, registryName);
    mesh::MeshManager::registerMesh(mesh, registryName);
}
