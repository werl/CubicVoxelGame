//
// Created by Peter Lewis on 2017-11-14.
//

#ifndef CUBICVOXELGAME_FILE_LOADER_HPP
#define CUBICVOXELGAME_FILE_LOADER_HPP

#include <string>

// TODO replace with universal file loader
class FileLoader {
private:
    std::string filePath;
    std::string contents;

public:
    FileLoader(std::string filePath);

    std::string getContents();

    std::string getFilePath();

    ~FileLoader();
};


#endif //CUBICVOXELGAME_FILE_LOADER_HPP
