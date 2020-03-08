#pragma once

#include "includes.hpp"

#ifndef SHADER_H
#define SHADER_H

class Shader
{
public:
    // Shader program ID
    uint ID;
    // Indicates if shader is correctly compiled and linked
    bool IsDefined = false;

    // Constructor reads and builds the shader (using private methods)
    Shader(const char* vertexPath, const char* fragmentPath);

    // Use/activate the shader
    void Use();
    // Utility uniform functions
    bool SetBool(const std::string& name, bool value) const;
    bool SetInt(const std::string& name, int value) const;
    bool SetFloat(const std::string& name, float value) const;
    bool SetMatrix4(const std::string& name, glm::mat4 value) const;

private:
    // Code of vertex and fragment shaders
    std::string vShaderCode;
    std::string fShaderCode;
    // IDs of vertex and fragment shaders
    uint vertexShader;
    uint fragmentShader;

    // Reads vertex and fragment shaders code from files into vShaderCode and fShaderCode
    bool readShaders(const char* vertexPath, const char* fragmentPath);
    // Compiles vertex and fragment shaders from vShaderCode and fShaderCode to vertexShader and fragmentShader
    bool compileShaders();
    // Creates shader program from vertexShader and fragmentShader and sets its id to ID
    bool linkShaderProgram();
    // Gets uniform location and returns -1 if unable to find
    int getUnifromLocation(const std::string& name) const;
    // Checks shader compilation/linking errors
    bool checkCompileErrors(uint shader, std::string type);
};

#endif