#include "includes.hpp"

#include "window.hpp"
#include "shader.hpp"
#include "model.hpp"
#include "cube.hpp"
#include "square.hpp"
#include "scene.hpp"

using namespace window;

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
    glViewport(0, 0, kWindowWidth, kWindowHeight);
    
    // TODO: Link shaders in compile-time or make it work when started from .exe
    Shader shader("vertexShader.vert", "fragmentShader.frag");
    if (!shader.IsDefined)
        return EXIT_FAILURE;

    // Projection matrix 
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)kWindowWidth / (float)kWindowHeight, 0.1f, 100.0f);

    // Create models and add them to a scene
    Scene scene(projection);
    Cube staticCube(glm::vec3(0.0f, 0.0f, 0.1f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.2f), &shader, "wall.jpg");
    if (!staticCube.IsDefined)
        return EXIT_FAILURE;
    scene.AddModel(&staticCube);

    Cube movingCube(glm::vec3(0.0f, 0.0f, 0.1f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.2f), &shader, "wall.jpg");
    if (!movingCube.IsDefined)
        return EXIT_FAILURE;
    scene.AddModel(&movingCube);

    Square floor(glm::vec3(), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f), &shader, "grass.jpg");
    if (!floor.IsDefined)
        return EXIT_FAILURE;
    scene.AddModel(&floor);

    // Create cameras
    Camera staticCamera(glm::vec3(-0.5f, -1.5f, 0.5f), glm::vec3(0.0f, 0.0f, 0.1f));
    Camera trackingCamera(glm::vec3(0.5f, -2.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.1f));
    Camera followingCamera(glm::vec3(-0.5f, 1.5f, 0.5f), glm::vec3(0.0f, 0.0f, 0.1f), false);
    trackingCamera.SetTargetModel(&movingCube);
    followingCamera.SetTargetModel(&movingCube);
    scene.AddCamera(&staticCamera);
    scene.AddCamera(&trackingCamera);
    scene.AddCamera(&followingCamera);

    // Lights
    Shader lightShader("lightVertexShader.vert", "lightFragmentShader.frag");
    if (!lightShader.IsDefined)
        return EXIT_FAILURE;
    Cube basicLightSource(glm::vec3(0.5f, 0.0f, 0.05f), 0.0f, glm::vec3(1.0f), glm::vec3(0.1f), &lightShader);
    if (!basicLightSource.IsDefined)
        return EXIT_FAILURE;
    scene.AddModel(&basicLightSource);

    float previousTime = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Process input
        processInput(window, &scene);

        // Lock FPS
        float time = (float)glfwGetTime();
        float deltaTime = time - previousTime;
        if (deltaTime < (1.0f / MaxFPS))
            continue;
        previousTime = time;

        // Clear the scene
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
        // Update models
        scene.Update();

        // Draw scene
        if (!scene.Draw())
            return EXIT_FAILURE;

        // Double buffering
        glfwSwapBuffers(window);
    }

    glfwTerminate();
	return EXIT_SUCCESS;
}