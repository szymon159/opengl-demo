#pragma once

#include "includes.hpp"

const char* basicFragmentShaderSource = "\
    #version 330 core\n\
    out vec4 fragmentColor;\n\
    in vec4 vertexColor;\n\
    uniform float intensityFactor;\n\
    void main()\n\
    {\n\
        fragmentColor = intensityFactor * vertexColor;\n\
    }\0";

uint compileBasicFragmentShader()
{
    uint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!fragmentShader)
        return FAILURE;
    glShaderSource(fragmentShader, 1, &basicFragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check fragment compilation result
    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");
        printf("%s\n", infoLog);
        return FAILURE;
    }

    return fragmentShader;
}