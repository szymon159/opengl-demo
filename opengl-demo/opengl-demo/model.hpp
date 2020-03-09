#pragma once

#include "includes.hpp"

#include "modelType.hpp"
#include "shader.hpp"

// TODO: Change unnecessary public variables to private
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
    Model(const float vertices[], uint verticesCount, glm::vec3 position, float angleDegrees, glm::vec3 rotationAxis, glm::vec3 scale, Shader* shader, std::string texturePath = "");
    
    glm::vec3 GetGlobalPosition();
    Shader* GetShader();
    void SetUpdateFunction(std::function<void(glm::vec3&, float&)> function);
    void Update();
    virtual bool Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, glm::vec3 lightPos, glm::vec3 lightColor);

protected:
	uint vaoId;
    uint textureId;
    uint verticesCount;
    glm::mat4 modelMatrix;
    Shader* shader;
    std::function<void(glm::vec3&, float&)> updateFunction = [](glm::vec3& position, float& roatationAngle) {};

    // Sets up VAO.
    // If modelType == Non-Textured: each vertex has coordinates xyz and normals xyz
    // Else: each vertex has coordinates xyz, normals xyz and textureCoordinates xy
    void setVAO(const float vertices[], ModelType modelType);
    // Loads texture
    void loadTexure(std::string texturePath);
    // Creates model matrix out of Position and AngleDegrees
    void updateModelMatrix();
};