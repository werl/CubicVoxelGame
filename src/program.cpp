//
// Created by Peter Lewis on 2017-11-17.
//

#include "program.hpp"

#include <spdlog/spdlog.h>

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

Program::Shader::Shader(const std::string shaderName, std::string filePath, gl::GLenum shaderType) {
    this->shaderName = shaderName;

    if(filePath.empty()) {
        shaderSuccess = false;
        return;
    }

    shaderID = gl::glCreateShader(shaderType);
    this->shaderType = shaderType;

    auto *p = new fs::path(filePath);

    std::string contents;
    fs::ifstream fileStream(*p);
    if(fileStream.is_open()) {
        std::string line;
        while(getline(fileStream, line)) {
            contents += "\n" + line;
        }
        fileStream.close();
    } else {
        shaderSuccess = false;
        spdlog::get("console")->error("File \"{}\" could not be read to create a shader\n", filePath);
    }

    delete p;

    const char *charContents = contents.c_str();
    gl::glShaderSource(shaderID, 1, &charContents, nullptr);
    gl::glCompileShader(shaderID);

    gl::GLboolean success;
    gl::glGetShaderiv(shaderID, gl::GL_COMPILE_STATUS, &success);

    if (success == gl::GL_FALSE) {
        gl::GLint logSize = 0;
        gl::glGetShaderiv(shaderID, gl::GL_INFO_LOG_LENGTH, &logSize);

        std::vector<char> errorLog(logSize);
        gl::glGetShaderInfoLog(shaderID, logSize, nullptr, &errorLog[0]);

        gl::glDeleteShader(shaderID);

        shaderSuccess = false;
        spdlog::get("console")->error("Shader \"{}\" failed to compile with the following error\n{}\n", shaderName, errorLog[0]);
    }

    shaderSuccess = true;
}

Program::Shader::~Shader() {
    gl::glDeleteShader(shaderID);
}

gl::GLenum Program::Shader::getShaderType() {
    return shaderType;
}

gl::GLuint Program::Shader::getShaderID() {
    return shaderID;
}

bool Program::Shader::isShaderSuccessful() {
    return shaderSuccess;
}

std::string Program::Shader::getShaderName() {
    return shaderName;
}

Program::Program(std::string programName, std::string vertPath, std::string tessCtrlPath, std::string tessEvalPath, std::string geoPath, std::string fragPath) {
    //TODO Implement full shader support
    spdlog::get("console")->error("Program \"{}\" is using a non-implemented version of the Program constructor. Please use the constructor with 2 parameters", programName);
}

Program::Program(std::string programName, std::string vertPath, std::string fragPath) {
    this->programName = programName;

    Shader vertexShader(programName + "_vertex", vertPath, gl::GL_VERTEX_SHADER);
    Shader fragmentShader(programName + "_fragment", fragPath, gl::GL_FRAGMENT_SHADER);

    if(vertexShader.isShaderSuccessful() && fragmentShader.isShaderSuccessful()) {
        programID = gl::glCreateProgram();

        gl::glAttachShader(programID, vertexShader.getShaderID());
        gl::glAttachShader(programID, fragmentShader.getShaderID());

        gl::glLinkProgram(programID);

        gl::GLboolean success;
        gl::glGetProgramiv(programID, gl::GL_LINK_STATUS, &success);

        if(success == gl::GL_FALSE) {
            programSuccess = false;
            gl::GLint logSize;
            gl::glGetProgramiv(programID, gl::GL_INFO_LOG_LENGTH, &logSize);

            std::vector<char> errorLog(logSize);
            gl::glGetProgramInfoLog(programID, logSize, nullptr, &errorLog[0]);

            spdlog::get("console")->error("Program \"{}\" failed to compile with the following error\n{s}\n", programName, errorLog[0]);
        } else {
            programSuccess = true;
        }
    } else if(!vertexShader.isShaderSuccessful()) {
        programSuccess = false;
        spdlog::get("console")->error("Shader \"{}\" failed to compile", vertexShader.getShaderName());
    } else {
        programSuccess = false;
        spdlog::get("console")->error("Shader \"{}\" failed to compile", fragmentShader.getShaderName());
    }

    gl::glDetachShader(programID, vertexShader.getShaderID());
    gl::glDetachShader(programID, fragmentShader.getShaderID());
}

Program::~Program() {
    gl::glDeleteProgram(programID);
}

void Program::useProgram() {
    gl::glUseProgram(programID);
}

void Program::detachProgram() {
    gl::glUseProgram(0);
}

bool Program::isProgramSuccess() {
    return programSuccess;
}

gl::GLuint Program::getProgramID() {
    return programID;
}
