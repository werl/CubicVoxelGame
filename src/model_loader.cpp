//
// Created by Peter Lewis on 2017-11-14.
//
#define TINYOBJLOADER_IMPLEMENTATION
#include "model_loader.hpp"

ModelLoader::ModelLoader(std::string fileName, std::string mtlDir) {
    this->fileName = fileName;
    this->mtlDir = mtlDir;
}

ModelLoader::ModelLoader(std::string fileName) {
    this->fileName = fileName;
}

bool ModelLoader::loadModel() {
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &error, fileName.c_str(), mtlDir.c_str());

    if (!error.empty()) {
        fprintf(stderr, "%s", error.c_str());
    }

    if (!ret) {
        fprintf(stderr, "Failed to load %s", fileName.c_str());
    }

    return ret;
}
