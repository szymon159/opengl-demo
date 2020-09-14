#pragma once
#include "includes.hpp"

#include "scene.hpp"

namespace window
{
    // This variable is needed as main loop operations are not capped to monitor refresh rate
    float MaxFPS = 60.0f;
    Scene* scene;

    void processInput(GLFWwindow* window, int key, int scancode, int action, int mods);

    void framebufferSize_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    GLFWwindow* createWindow()
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
        MaxFPS = (float)mode->refreshRate;

#ifdef _DEBUG
        monitor = NULL;
#endif // DEBUG

        GLFWwindow* window = glfwCreateWindow(kWindowWidth, kWindowHeight, WINDOW_TITLE, monitor, NULL);
        if (window == NULL)
        {
            printf("Failed to create GLFW window\n");
            glfwTerminate();
            return window;
        }
        glfwMakeContextCurrent(window);

        glfwSetFramebufferSizeCallback(window, framebufferSize_callback);

        glfwSetKeyCallback(window, processInput);

        return window;
    }

    // Keys:
    //
    // ESC - close
    //
    // Cameras:
    // 1 - static
    // 2 - tracking (not moving)
    // 3 - following (moving)
    //
    // Display mode:
    // Q - filled polygons
    // E - wireframe of polygons
    //
    // Shader:
    // G - toggle using Gouraud shading (default Phong)
    //
    // Lighting:
    // B - toggle using Blinn lightin (default Blinn)
    void processInput(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        // Cameras
        if (key == GLFW_KEY_1 && action == GLFW_PRESS)
        {
            scene->ToggleActiveCamera(0);
        }
        else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
        {
            scene->ToggleActiveCamera(1);
        }
        else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
        {
            scene->ToggleActiveCamera(2);
        }
        // Display mode
        else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        }
        else if (key == GLFW_KEY_E && action == GLFW_PRESS)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        // Close
        else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }
        // Toggle gouraud shading
        else if (key == GLFW_KEY_G && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }
        // Toggle Blinn lighting model
        else if (key == GLFW_KEY_B && action == GLFW_PRESS)
        {
            scene->ToggleBlinnLighting();
        }
    }
}