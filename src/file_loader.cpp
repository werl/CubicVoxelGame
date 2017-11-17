//
// Created by Peter Lewis on 2017-11-14.
//

#include "file_loader.hpp"
#include <iostream>
#include <fstream>

using namespace std;

FileLoader::FileLoader(string filePath) {
    this->filePath = filePath;


    ifstream fileStream(filePath, ios::in);
    if(fileStream.is_open()) {
        string line = "";
        while (getline(fileStream, line)) {
            contents += "\n" + line;
        }
        fileStream.close();
    } else {
        throw "file " + filePath + " could not be found";
    }
}

string FileLoader::getContents() {
    return contents;
}

string FileLoader::getFilePath() {
    return filePath;
}

FileLoader::~FileLoader() {

}
