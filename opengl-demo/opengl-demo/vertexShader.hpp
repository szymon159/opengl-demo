#pragma once

#include "includes.hpp"

const char* basicVertexShaderSource = "\
    #version 330 core\n\
    layout (location = 0) in vec3 aPos;\n\
    out vec4 vertexColor;\n\
    void main()\n\
    {\n\
        gl_Position = vec4(aPos, 1.0);\n\
        vertexColor = (gl_Position + 1) / 2;\n\
    }\0";

uint compileBasicVertexShader()
{
    uint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if (!vertexShader)
        return FAILURE;
    glShaderSource(vertexShader, 1, &basicVertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check vertex compilation result
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
        printf("%s\n", infoLog);
        return FAILURE;
    }

    return vertexShader;
}