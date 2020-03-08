#pragma once

#include "includes.hpp"

#include "shader.hpp"

// TODO: Move methods' implementation to .cpp file
class Model
{
public:
    // Indicates if model is correctly created and texture is loaded
    bool IsDefined = false;

    // XYZ position of the center of model
    glm::vec3 Position;
    // Rotation angle in degrees
    float AngleDegrees;
    // The axis to rotate around
    glm::vec3 RotationAxis;
    // Vector indicating the scale by each axis
    glm::vec3 Scale;

    // Binds model with following vertices to VAO and sets its location and texture attributes (if path not empty)
    // Vertices is the array with 3 or 5 values for each vetex: coordinates xyz and textureCoordinates xy (if path not empty)
    Model(const float vertices[], uint verticesCount, glm::vec3 position, float angleDegrees, glm::vec3 rotationAxis, glm::vec3 scale, Shader *shader, std::string texturePath = "")
        :verticesCount(verticesCount), Position(position), AngleDegrees(angleDegrees), RotationAxis(rotationAxis), Scale(scale), shader(shader)
	{
        // Check if model has texture or not
        int paramCount = texturePath == "" ? 1 : 2;

        setVAO(vertices, paramCount);
        if (!vaoId)
            return;

        if (texturePath != "")
        {
            loadTexure(texturePath);
            IsDefined = textureId != 0;
        }

        updateModelMatrix();
	}

    glm::vec3 GetGlobalPosition()
    {
        return modelMatrix * glm::vec4(Position, 1.0f);
    }

    // TODO: Do this automatically based on some lambda expression defined at the beginning
    void Update()
    {
        Position.x = sin(glfwGetTime());

        updateModelMatrix();
    }

    bool Draw(const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix)
    {
        glm::mat4 transformationMatrix = projectionMatrix * viewMatrix * modelMatrix;
        
        // Asssign uniforms for shaders
        if (!shader->setInt("texture1", 0) ||
            !shader->setMatrix4("transform", transformationMatrix))
        {
            return FAILURE;
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glBindVertexArray(vaoId);
        glDrawArrays(GL_TRIANGLES, 0, verticesCount);

        return SUCCESS;
    }

private:
	uint vaoId;
    uint textureId;
    uint verticesCount;
    glm::mat4 modelMatrix;
    Shader* shader;

    // Sets up VAO.
    // If paramCount == 1: each vertex has coordinates xyz
    // Else: each vertex has coordinates xyz and textureCoordinates xy
    void setVAO(const float vertices[], int paramCount)
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

    // Creates model matrix out of Position and AngleDegrees
    void updateModelMatrix()
    {
        modelMatrix = glm::scale(glm::mat4(1.0f), Scale);
        modelMatrix = glm::translate(modelMatrix, Position);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(AngleDegrees), RotationAxis);
    }
};