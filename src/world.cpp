//
// Created by Peter Lewis on 2017-11-20.
//

#include "world.hpp"
#include "mesh_manager.hpp"

world::World::World(int width, int height) : tiles(boost::multi_array<tile::TileBase, 2>(boost::extents[width][height])) {
    this->width = width;
    this->height = height;

    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            auto t = tile::TileBase::getTile("grass");
            t.get().setPosition(glm::vec3(x, 0, y));
            tiles[x][y] = t.get();
        }
    }
}

world::World::~World() = default;

void world::World::render(Program *prog) {
    for(int i = 0; i < width; i ++) {
        for(int j = 0; j < height; j ++) {
            Mesh *mesh = mesh::MeshManager::getMesh(tiles[i][j].getMeshRegistryName());
            mesh->render(tiles[i][j].getPosition(), prog->getProgramID());
        }
    }
}
