#include "model.hpp"

// Public methods
//
Model::Model(const float vertices[], uint verticesCount, glm::vec3 position, float angleDegrees, glm::vec3 rotationAxis, glm::vec3 scale, Shader* shader, std::string texturePath)
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
    IsDefined = true;
}

glm::vec3 Model::GetGlobalPosition()
{
    return modelMatrix * glm::vec4(1.0f);
}

// TODO: Do this automatically based on some lambda expression defined at the beginning
void Model::Update()
{
    const float radius = 0.8f;

    Position.x = (float)sin(glfwGetTime()) * radius;
    Position.y = (float)cos(glfwGetTime()) * radius;

    updateModelMatrix();
}

bool Model::Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    shader->Use();
    glm::mat4 transformationMatrix = projectionMatrix * viewMatrix * modelMatrix;

    // Asssign uniforms for shaders
    if ((textureId != 0 && !shader->SetInt("texture1", 0)) ||
        !shader->SetMatrix4("transform", transformationMatrix))
    {
        return FAILURE;
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glBindVertexArray(vaoId);
    glDrawArrays(GL_TRIANGLES, 0, verticesCount);
    glUseProgram(0);

    return SUCCESS;
}
//


//Private methods
//
void Model::setVAO(const float vertices[], int paramCount)
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

void Model::loadTexure(std::string texturePath)
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

void Model::updateModelMatrix()
{
    modelMatrix = glm::translate(glm::mat4(1.0f), Position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(AngleDegrees), RotationAxis);
    modelMatrix = glm::scale(modelMatrix, Scale);
}
//