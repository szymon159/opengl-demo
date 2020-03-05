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
uint initializeRectangle()
{
    float vertices[] =
    {
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,   // top left 
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return VAO;
}

int main()
{
    GLFWwindow* window;

    if (!initializeGLFW() 
        || !(window = createWindow())
        || !initializeGLAD())
        return EXIT_FAILURE;

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    uint shaderProgram;
    if (!(shaderProgram = applyShaders()))
        return EXIT_FAILURE;

    // Get VAO corresponding to default triangle
    uint VAO = initializeRectangle();

    while (!glfwWindowShouldClose(window))
    {
        // Process input
        processInput(window);

        // Clear the scene
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Configure shaders
        float timeValue = glfwGetTime();
        float intensityFactor = (sin(timeValue) / 2.0f) + 0.5f;
        int intensityFactorLocation = glGetUniformLocation(shaderProgram, "intensityFactor");
        if (intensityFactorLocation == -1)
        {
            printf("Unable to find uniform: intensityFactor\n");
            return EXIT_FAILURE;
        }
        glUseProgram(shaderProgram);
        glUniform1f(intensityFactorLocation, intensityFactor);
        
        // Draw object referenced by VAO
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Double buffering
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
	return EXIT_SUCCESS;
}