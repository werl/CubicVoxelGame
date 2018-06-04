//
// Created by Peter Lewis on 2017-11-20.
//

#ifndef CUBICVOXELGAME_REGISTRY_HPP
#define CUBICVOXELGAME_REGISTRY_HPP

#include "tile_base.hpp"
#include "mesh_manager.hpp"
#include "mesh.hpp"

#include <string>

void registerTileAndMesh(tile::TileBase &tile, Mesh &mesh, std::string registryName);

#endif //CUBICVOXELGAME_REGISTRY_HPP
