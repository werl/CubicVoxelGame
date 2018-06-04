//
// Created by Peter Lewis on 2017-11-17.
//

#ifndef CUBICVOXELGAME_PROGRAM_HPP
#define CUBICVOXELGAME_PROGRAM_HPP

#include <glbinding/gl41/gl.h>

class Program {
public:
    struct Shader {
    private:
        gl::GLuint shaderID;
        gl::GLenum shaderType;
        bool shaderSuccess;
        std::string shaderName;

    public:
        explicit Shader(std::string shaderName, std::string filePath, gl::GLenum shaderType);
        ~Shader();

        gl::GLenum getShaderType();
        gl::GLuint getShaderID();
        bool isShaderSuccessful();
        std::string getShaderName();

    };

private:
    gl::GLuint programID;
    std::string programName;
    bool programSuccess;

public:
    /**
     * NOT IMPLEMENTED YET
     * Used to add up to all supported shader types to a program
     * @param vertPath - Path to the vertex shader file
     * @param tessCtrlPath - Path to the tessellation control shader file
     * @param tessEvalPath - Path to the tessellation evaluation shader file
     * @param geoPath - Path to the geometry shader file
     * @param fragPath - Path to the fragment shader file
     */
    Program(std::string programName, std::string vertPath, std::string tessCtrlPath, std::string tessEvalPath, std::string geoPath, std::string fragPath);
    /**
     * Used to create more simple programs that only use vertex and fragment shaders
     * @param vertPath - Path to the vertex shader file
     * @param fragPath - Path to the fragment shader file
     */
    Program(std::string programName, std::string vertPath, std::string fragPath);
    ~Program();

    /**
     * Use the program
     */
    void useProgram();
    /**
     * Sop using the program
     */
    void detachProgram();
    /**
     * @return - if the program creation was successful
     */
    bool isProgramSuccess();

    gl::GLuint getProgramID();

};


#endif //CUBICVOXELGAME_PROGRAM_HPP
