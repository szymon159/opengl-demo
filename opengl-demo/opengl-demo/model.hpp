#pragma once

#include "includes.hpp"

#include "mesh.hpp"
#include "textureType.hpp"
#include "material.hpp"

class Texture;
class Shader;
class Scene;

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
    // Material of which object is created
    Material ModelMaterial;

    // Constructs the model from given object file
    Model(glm::vec3 position, float angleDegrees, glm::vec3 rotationAxis, glm::vec3 scale, Scene* ownerScene, std::string texturePath, const Material& material);

    glm::vec3 GetGlobalPosition();
    void SetUpdateFunction(std::function<void(glm::vec3&, float&)> function);
    void Update();
    virtual bool Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, glm::vec3 viewPos);

protected:
    glm::mat4 modelMatrix;
    std::function<void(glm::vec3&, float&)> updateFunction = [](glm::vec3& position, float& roatationAngle) {};
    std::vector<Mesh> meshes;
    std::string texturesDir;
    Scene* ownerScene;
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