#pragma once

#include "includes.hpp"

#include "mesh.hpp"
#include "textureType.hpp"

class Texture;
class Shader;

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
    Model(const float vertices[], uint verticesCount, glm::vec3 position, float angleDegrees, glm::vec3 rotationAxis, glm::vec3 scale, Shader* shader, std::string texturePath);
    
    glm::vec3 GetGlobalPosition();
    Shader* GetShader();
    void SetUpdateFunction(std::function<void(glm::vec3&, float&)> function);
    void Update();
    virtual bool Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos);

protected:
    glm::mat4 modelMatrix;
    Shader* shader;
    std::function<void(glm::vec3&, float&)> updateFunction = [](glm::vec3& position, float& roatationAngle) {};
    std::vector<Mesh> meshes;
    // TODO: Move to scene
    std::vector<Texture> loadedTextures;

    // Creates model matrix out of Position and AngleDegrees
    void updateModelMatrix();
    // Loads texture
    void loadModel(std::string modelPath);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType textureType);
};