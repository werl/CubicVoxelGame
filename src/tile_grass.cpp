//
// Created by Peter Lewis on 2017-11-20.
//

#include "tile_grass.hpp"

tile::TileGrass::TileGrass() : TileBase("grass", "grass") {

}

tile::TileGrass::TileGrass(const TileGrass &obj) : TileBase(obj) {

}

std::string tile::TileGrass::getMeshRegistryName() {
    return "grass";
}
