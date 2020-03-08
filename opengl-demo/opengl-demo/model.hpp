#pragma once

#include "includes.hpp"

// Rectangle
//float vertices[] =
//{
//    // positions        // texture
//     1.0f,  1.0f, 0.0f, 1.0f, 1.0f, // top right
//     1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom right
//    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom left
//    -1.0f,  1.0f, 0.0f, 0.0f, 1.0f  // top left 
//};

class Model
{
public:
    // Indicates if model is correctly created and texture is loaded
    bool IsDefined = false;

    // Binds model with following vertices to VAO and sets its location
    // Vertices is the array with 3 values for each vetex: coordinates xyz
    Model(const float vertices[], uint verticesCount, glm::mat4 modelMatrix)
        :verticesCount(verticesCount), modelMatrix(modelMatrix)
    {
        setVAO(vertices, verticesCount, 1);
        if (!vaoId)
            return;
    }

    // Binds model with following vertices to VAO and sets its location and texture attributes
    // Vertices is the array with 5 values for each vetex: coordinates xyz, textureCoordinates xy
    Model(const float vertices[], uint verticesCount, std::string texturePath, glm::mat4 modelMatrix)
        :verticesCount(verticesCount), modelMatrix(modelMatrix)
	{
        setVAO(vertices, verticesCount, 2);
        if (!vaoId)
            return;

        loadTexure(texturePath);
        IsDefined = textureId != 0;
	}

    void Draw()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glBindVertexArray(vaoId);
        glDrawArrays(GL_TRIANGLES, 0, verticesCount);
    }

private:
	uint vaoId;
    uint textureId;
    uint verticesCount;
    glm::mat4 modelMatrix;

    // Sets up VAO.
    // If paramCount == 1: each vertex has coordinates xyz
    // Else: each vertex has coordinates xyz and textureCoordinates xy
    void setVAO(const float vertices[], uint verticesCount, int paramCount)
    {
        int stride = paramCount == 1 ? 3 * sizeof(float) : 5 * sizeof(float);
        int verticesSize = stride * verticesCount;

        uint VBO;
        glGenVertexArrays(1, &vaoId);
        glGenBuffers(1, &VBO);

        glBindVertexArray(vaoId);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

        // Set vertex attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(0);
        if (paramCount == 2)
        {
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
        }

        // Unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    // Loads texture
    void loadTexure(std::string texturePath)
    {
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        // Set texture wrapping/filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int texWidth, texHeight, texChannelsNumber;
        stbi_set_flip_vertically_on_load(true);
        uchar* data = stbi_load(texturePath.c_str(), &texWidth, &texHeight, &texChannelsNumber, 0);
        if (!data)
        {
            printf("Unable to load texture: %s", texturePath.c_str());
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
};