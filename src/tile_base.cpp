//
// Created by Peter Lewis on 2017-11-20.
//

#include "tile_base.hpp"
#include <spdlog/spdlog.h>

tile::TileBase::TileBase(std::string tileName, std::string unlocalizedName) {
    this->name = tileName;
    this->uName = unlocalizedName;
}

tile::TileBase::TileBase(const tile::TileBase &obj) {
    rotation = obj.rotation;

    name = obj.name;
    uName = obj.uName;
}

tile::TileBase::TileBase() : TileBase("invalid", "invalid"){

}

tile::TileBase::~TileBase() = default;

std::string tile::TileBase::getTileName() {
    return name;
}

std::string tile::TileBase::getUnlocalizedName() {
    return uName;
}

glm::vec3* tile::TileBase::getPosition() {
    return &position;
};

void tile::TileBase::setPosition(glm::vec3 pos) {
    position = pos;
}

std::map<std::string, tile::TileBase*>* tile::TileBase::getTileMap(){
    static auto *tiles = new std::map<std::string, tile::TileBase*>();
    return tiles;
};

void tile::TileBase::registerTile(TileBase &tile, std::string name) {
    std::shared_ptr<spdlog::logger> console = spdlog::get("console");
    auto *tiles = tile::TileBase::getTileMap();

    auto found = tiles->find(name);
    if(found != tiles->end()) {
        console->critical("Duplicate tile name registration was attempted: \"{}\"", name);
        return;
    }
    tiles->insert(std::pair<std::string, tile::TileBase*>(name, &tile));
    console->info("Successfully register tile \"{}\"\n", name);
}

std::string tile::TileBase::getMeshRegistryName() {
    return name;
}

boost::optional<tile::TileBase> tile::TileBase::getTile(std::string tile_name) {
    try {
        TileBase ret = *tile::TileBase::getTileMap()->at(tile_name);
        return ret;
    } catch(const std::out_of_range &err) {
        spdlog::get("console")->error("{}\n", err.what());
        return boost::optional<tile::TileBase>();
    }
}

boost::optional<tile::TileBase*> tile::TileBase::getTilePointer(std::string tile_name) {
    try {
        TileBase* ret = tile::TileBase::getTileMap()->at(tile_name);
        return ret;
    } catch(const std::out_of_range &err) {
        spdlog::get("console")->error("{}\n", err.what());
        return boost::optional<tile::TileBase*>();
    }
}
