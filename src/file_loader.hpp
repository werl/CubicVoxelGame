//
// Created by Peter Lewis on 2017-11-14.
//

#ifndef TRANSPORTCONCEPT2D_FILE_LOADER_HPP
#define TRANSPORTCONCEPT2D_FILE_LOADER_HPP

#include <string>

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


#endif //TRANSPORTCONCEPT2D_FILE_LOADER_HPP
