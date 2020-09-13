#include "mesh.hpp"

#include "shader.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint> indices, std::vector<Texture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
}

void Mesh::Draw(Shader*& shader) const
{
    uint diffuseCount = 1;
    uint specularCount = 1;
    for (int i = 0; i < textures.size(); i++)
    {
        // Activate proper texture unit before binding
        glActiveTexture(GL_TEXTURE0 + i);

        std::string textureNumber;
        switch (textures[i].Type)
        {
        case TextureType::Diffuse:
            textureNumber = std::to_string(diffuseCount++);
            break;
        case TextureType::Specular:
            textureNumber = std::to_string(specularCount++);
            break;
        }
    
        shader->SetFloat(("material." + textures[i].GetTextureName() + textureNumber).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].Id);
    }

    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(vaoId);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::setupMesh()
{
    setVAO();
}

void Mesh::setVAO()
{
    uint VBO, EBO;
    glGenVertexArrays(1, &vaoId);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(vaoId);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint), &indices[0], GL_STATIC_DRAW);

    // Set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
