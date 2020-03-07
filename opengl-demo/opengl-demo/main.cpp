#include "includes.hpp"

#include "window.hpp"
#include "shader.hpp"

using namespace Window;

// TODO: Move to another file when refactoring
int initializeGLFW()
{
    if (!glfwInit())
        return FAILURE;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return SUCCESS;
}

int initializeGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return FAILURE;
    }

    return SUCCESS;
}
//

// TODO: Move this method somewhere else (but probably will be deleted in the meantime)
uint initializeModel()
{
    // Rectangle
    //float vertices[] =
    //{
    //    // positions        // texture
    //     1.0f,  1.0f, 0.0f, 1.0f, 1.0f, // top right
    //     1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom right
    //    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom left
    //    -1.0f,  1.0f, 0.0f, 0.0f, 1.0f  // top left 
    //};

    // Cuboid
    float vertices[] = 
    {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    // Indices of vertices creating triangles creating rectangle
    uint indices[] =
    {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // Copy and bind vertices to opengl buffer
    uint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return VAO;
}

// TODO: Move it
uint loadTexture(std::string texturePath)
{
    uint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

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
        return FAILURE;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    return texture;
}

// TODO: Move it somewhere
glm::mat4 createTransformationMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);
    // Rectangle
    //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // Cuboid
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 100.0f);

    return projection * view * model;
}

int main()
{
    GLFWwindow* window;

    if (!initializeGLFW() 
        || !(window = createWindow())
        || !initializeGLAD())
        return EXIT_FAILURE;

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    // TODO: Link shaders in compile-time or make it work when started from .exe
    Shader shader("vertexShader.vert", "fragmentShader.frag");
    if (!shader.IsDefined)
        return EXIT_FAILURE;

    // Get VAO corresponding to default triangle
    uint VAO = initializeModel();

    // Load textures
    // TODO: Change this hardcoded "2"
    uint texture[2];
    std::string texturePath[2] = { "wall.jpg", "face.png" };
    for (int i = 0; i < 2; i++)
    {
        texture[i] = loadTexture(texturePath[i]);
        if (!texture[i])
            return EXIT_FAILURE;
    }

    while (!glfwWindowShouldClose(window))
    {
        // Process input
        processInput(window);

        // Clear the scene
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Run shaders
        shader.use();

        // Compute transformations
        float intensityFactor = (sin(glfwGetTime()) / 2.0f) + 0.5f;
        glm::mat4 transform = createTransformationMatrix();

        // Asssign uniforms for shaders
        if (!shader.setFloat("intensityFactor", intensityFactor) ||
            !shader.setInt("texture1", 0) ||
            !shader.setInt("texture2", 1) ||
            !shader.setMatrix4("transform", transform))
            return EXIT_FAILURE;
        
        // Draw object referenced by VAO
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        glBindVertexArray(VAO);
        // Rectangle
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // Cuboid
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Double buffering
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
	return EXIT_SUCCESS;
}