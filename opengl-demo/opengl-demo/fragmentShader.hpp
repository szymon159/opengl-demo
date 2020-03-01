#pragma once

#include "includes.hpp"

const char* orangeFragmentShaderSource = "\
    #version 330 core\n\
    out vec4 fragmentColor;\n\
    void main()\n\
    {\n\
        fragmentColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n\
    }\0";

uint compileOrangeFragmentShader()
{
    uint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!fragmentShader)
        return FAILURE;
    glShaderSource(fragmentShader, 1, &orangeFragmentShaderSource, NULL);
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