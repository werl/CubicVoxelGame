//
// Created by Peter Lewis on 2017-11-14.
//

#ifndef TRANSPORTCONCEPT2D_MODEL_LOADER_HPP
#define TRANSPORTCONCEPT2D_MODEL_LOADER_HPP

#include <string>

#include "tiny_obj_loader.h"

class ModelLoader {
private:
    std::string fileName;
    std::string mtlDir;
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string error;

public:
    ModelLoader(std::string fileName, std::string mtlDir);

    explicit ModelLoader(std::string fileName);

    bool loadModel();

};


#endif //TRANSPORTCONCEPT2D_MODEL_LOADER_HPP
