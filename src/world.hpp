//
// Created by Peter Lewis on 2017-11-20.
//

#ifndef TRANSPORTCONCEPT2D_WORLD_HPP
#define TRANSPORTCONCEPT2D_WORLD_HPP

#include "tile_base.hpp"
#include "program.hpp"
#include <boost/multi_array.hpp>

namespace world {
    class World {
    private:
        boost::multi_array<tile::TileBase, 2> tiles;
        int width;
        int height;

    public:
        World(int width, int height);
        ~World();

        void render(Program *prog);
    };
}

#endif //TRANSPORTCONCEPT2D_WORLD_HPP
