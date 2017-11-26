//
// Created by Peter Lewis on 2017-11-20.
//

#ifndef TRANSPORTCONCEPT2D_TILE_BASE_HPP
#define TRANSPORTCONCEPT2D_TILE_BASE_HPP

#include "mesh.hpp"
#include <glm/glm.hpp>
#include <string>
#include <map>
#include <boost/optional.hpp>


namespace tile {
    class TileBase {
    private:
    protected:
        glm::quat *rotation;
        std::string name;
        std::string uName;
        glm::vec3 position;

    public:
        TileBase(std::string tileName, std::string unlocalizedName);
        TileBase(const TileBase &obj);
        /**
         * DO NOT USE. FOR INTERNAL USE ONLY
         */
        TileBase();
        ~TileBase();

        std::string getTileName();
        std::string getUnlocalizedName();
        glm::vec3* getPosition();
        void setPosition(glm::vec3 pos);

        virtual std::string getMeshRegistryName();

        static std::map<std::string, TileBase*>* getTileMap();
        static void registerTile(TileBase &tile, std::string name);
        static boost::optional<tile::TileBase> getTile(std::string tile_name);
        static boost::optional<tile::TileBase*> getTilePointer(std::string tile_name);

    };
}

#endif //TRANSPORTCONCEPT2D_TILE_BASE_HPP
