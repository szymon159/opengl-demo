#include "includes.hpp"

#include "window.hpp"
#include "shader.hpp"
#include "model.hpp"
#include "lightModel.hpp"
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
    Shader shader("gouraudVertexShader.vert", "gouraudFragShader.frag");
    //Shader shader("phongVertexShader.vert", "phongFragShader.frag");
    if (!shader.IsDefined)
        return EXIT_FAILURE;

    // Projection matrix 
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)kWindowWidth / (float)kWindowHeight, 0.1f, 100.0f);

    // Create models and add them to a scene
    Scene scene(projection);

    Model staticCube(glm::vec3(0.0f, 0.0f, 0.1f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.002f), &shader, modelpth, glm::vec3(1.f, 0.f, 0.f));
    if (!staticCube.IsDefined)
        return EXIT_FAILURE;
    scene.AddModel(&staticCube);

    Model movingCube(glm::vec3(0.0f, 0.0f, 0.1f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.002f), &shader, modelpth, glm::vec3(0.f, 1.f, 0.f));
    if (!movingCube.IsDefined)
        return EXIT_FAILURE;
    // TODO: Move it
    std::function<void(glm::vec3&, float&)> moving_cube_update_func = [](glm::vec3& position, float& rotationAngle) {
        const float radius = 0.8f;

        position.x = (float)sin(glfwGetTime()) * radius;
        position.y = (float)cos(glfwGetTime()) * radius;
        rotationAngle = 100.0f * glfwGetTime();
    };
    movingCube.SetUpdateFunction(moving_cube_update_func);
    scene.AddModel(&movingCube);

    Model floor(glm::vec3(0.f, -3.f, -0.1f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(50.f, 10.f, 0.00001f), &shader, "models/cube.obj", glm::vec3(0.f, 0.f, 1.f));
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
    scene.SetAmbient(0.2f, glm::vec3(1.0f));
    Shader lightShader("phongVertexShader.vert", "phongFragShader.frag");
    //Shader lightShader("lightVertexShader.vert", "lightFragmentShader.frag");
   if (!lightShader.IsDefined)
        return EXIT_FAILURE;
    LightModel basicLightSource(glm::vec3(0.0f, 0.0f, 1.f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0002f), &lightShader, glm::vec3(0.f, 0.f, 0.f));
    if (!basicLightSource.IsDefined)
        return EXIT_FAILURE;
    scene.AddLight(&basicLightSource);

    float previousTime = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Process input
        processInput(window, &scene);

        // Lock FPS to 2 * MaxFPS
        float time = (float)glfwGetTime();
        float deltaTime = time - previousTime;
        if (deltaTime < (0.5f / MaxFPS))
            continue;
        previousTime = time;

        // Clear the scene
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
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