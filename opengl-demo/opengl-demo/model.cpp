#include "model.hpp"

#include "vertex.hpp"
#include "shader.hpp"
#include "texture.hpp"

// Public methods
//
Model::Model(const float vertices[], uint verticesCount, glm::vec3 position, float angleDegrees, glm::vec3 rotationAxis, glm::vec3 scale, Shader* shader, std::string texturePath)
    : Position(position), AngleDegrees(angleDegrees), RotationAxis(rotationAxis), Scale(scale), shader(shader)
{
    loadModel(texturePath);

    updateModelMatrix();
    IsDefined = true;
}

glm::vec3 Model::GetGlobalPosition()
{
    return modelMatrix * glm::vec4(1.0f);
}

Shader* Model::GetShader()
{
    return shader;
}

void Model::SetUpdateFunction(std::function<void(glm::vec3&, float&)> function)
{
    updateFunction = function;
}

void Model::Update()
{
    updateFunction(Position, AngleDegrees);

    updateModelMatrix();
}

bool Model::Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos)
{
    shader->Use();
    glm::mat4 transformationMatrix = projectionMatrix * viewMatrix * modelMatrix;

    // Asssign uniforms for shaders
    if (!shader->SetMatrix4("transform", transformationMatrix) ||
        !shader->SetMatrix4("modelMatrix", modelMatrix) ||
        !shader->SetMatrix4("inversedModelMatrix", glm::inverse(modelMatrix)) ||
        !shader->SetVec3("lightPos", lightPos) ||
        !shader->SetVec3("lightColor", lightColor) ||
        !shader->SetVec3("viewPos", viewPos))
    {
        return FAILURE;
    }

    // Draw all the meshes
    for (const auto& mesh : meshes)
    {
        mesh.Draw(shader);
    }

    return SUCCESS;
}
//


//Private methods
//
//void Model::setVAO(const float vertices[], ModelType modelType)
//{
//    int stride = modelType == ModelType::NonTextured ? 6 * sizeof(float) : 8 * sizeof(float);
//    int verticesSize = stride * verticesCount;
//
//    uint VBO;
//    glGenVertexArrays(1, &vaoId);
//    glGenBuffers(1, &VBO);
//
//    glBindVertexArray(vaoId);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
//
//    // Set vertex attributes
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//    if (modelType == ModelType::Textured)
//    {
//        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
//        glEnableVertexAttribArray(2);
//    }
//
//    // Unbind
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//}

void Model::loadModel(std::string texturePath)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(texturePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        printf("ERROR::ASSIMP::%s\n", import.GetErrorString());
        return;
    }
    auto directory = texturePath.substr(0, texturePath.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    // Process all the node's meshes (if any)
    for (uint i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // Then do the same for each of its children
    for (uint i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices(mesh->mNumVertices);
    std::vector<uint> indices;
    std::vector<Texture> textures;

    // Load all the vertices
    for (uint i = 0; i < mesh->mNumVertices; i++)
    {
        vertices[i].Poistion = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
        
        if (mesh->HasNormals())
            vertices[i].Normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
        else
            vertices[i].Normal = glm::vec3(0.0);

        if (mesh->HasTextureCoords(0))
            vertices[i].TexCoords = { mesh->mTextureCoords[0][i].x,  mesh->mTextureCoords[0][i].y };
        else
            vertices[i].TexCoords = glm::vec2(0.0);
    }

    // Load all the indices
    for (uint i = 0; i < mesh->mNumFaces; i++)
    {
        auto face = mesh->mFaces[i];
        for (uint j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Load all the materials
    if (mesh->mMaterialIndex >= 0)
    {
        auto material = scene->mMaterials[mesh->mMaterialIndex];

        auto diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::Diffuse);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        auto specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::Specular);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType textureType)
{
    std::vector<Texture> textures(mat->GetTextureCount(type));
    for (uint i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        
        auto shouldSkip = false;
        for (uint j = 0; j < loadedTextures.size(); j++)
        {
            if (std::strcmp(loadedTextures[j].Path.data(), str.C_Str()) == 0)
            {
                textures[i] = loadedTextures[j];
                shouldSkip = true;
                break;
            }
        }

        if (!shouldSkip)
            textures[i] = Texture(str.C_Str(), textureType);

    }
    return textures;
}

void Model::updateModelMatrix()
{
    modelMatrix = glm::translate(glm::mat4(1.0f), Position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(AngleDegrees), RotationAxis);
    modelMatrix = glm::scale(modelMatrix, Scale);
}
//