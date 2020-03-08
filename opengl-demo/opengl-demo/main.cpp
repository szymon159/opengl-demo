#include "includes.hpp"

#include "window.hpp"
#include "shader.hpp"
#include "model.hpp"
#include "cuboid.hpp"
#include "rectangle.hpp"
#include "scene.hpp"

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

    // View and projection matrices
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 100.0f);

    // Create models and add them to a scene
    Scene scene(view, projection);
    Cuboid cube(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f), glm:: vec3(0.5f), &shader, "wall.jpg");
    if (!cube.IsDefined)
        return EXIT_FAILURE;
    scene.AddModel(&cube);

    Rectangle rect(glm::vec3(), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f), &shader, "grass.jpg");
    if (!rect.IsDefined)
        return EXIT_FAILURE;
    scene.AddModel(&rect);
    
    while (!glfwWindowShouldClose(window))
    {
        // Process input
        processInput(window);

        // Clear the scene
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Run shaders
        shader.use();
        
        // Update models
        //cube.Update(glm::vec3(), (float)glfwGetTime() * 50.0f);

        // Draw scene
        if (!scene.Draw())
            return EXIT_FAILURE;

        // Double buffering
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
	return EXIT_SUCCESS;
}