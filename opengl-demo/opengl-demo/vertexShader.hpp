#pragma once

#include "includes.hpp"

const char* basicVertexShaderSource = "\
    #version 330 core\n\
    layout (location = 0) in vec3 aPos;\n\
    void main()\n\
    {\n\
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n\
    }\0";

int compileBasicVertexShader()
{
    uint vertexShader = glCreateShader(GL_VERTEX_SHADER);
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
    }

    return success;
}