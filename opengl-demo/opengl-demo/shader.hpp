#pragma once

#include "includes.hpp"

#include "vertexShader.hpp"
#include "fragmentShader.hpp"

uint applyShaders()
{
    uint vertexShader = compileBasicVertexShader();
    uint fragmentShader = compileOrangeFragmentShader();
    if (!vertexShader
        || !fragmentShader)
        return FAILURE;

    uint shaderProgram = glCreateProgram();
    if (!shaderProgram)
        return FAILURE;

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check linking result
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        // TODO: Format line below to correspond type of error
        printf("ERROR::PROGRAM::SHADER::LINKING_FAILED\n");
        printf("%s\n", infoLog);
        return FAILURE;
    }

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}