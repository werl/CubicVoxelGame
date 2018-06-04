//
// Created by Peter Lewis on 2017-11-20.
//

#ifndef CUBICVOXELGAME_TILE_GRASS_HPP
#define CUBICVOXELGAME_TILE_GRASS_HPP

#include "tile_base.hpp"

namespace tile {
    class TileGrass : public tile::TileBase {
    public:
        TileGrass();
        TileGrass(const TileGrass &obj);

        virtual std::string getMeshRegistryName();
    };
}

#endif //CUBICVOXELGAME_TILE_GRASS_HPP
