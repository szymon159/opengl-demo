#pragma once
#include "includes.hpp"

#include "scene.hpp"

namespace Window
{
    // HACK: This variable is needed as main loop operations are not capped as drawing
    float MaxFPS = 60.0f;

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
        GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, monitor, NULL);
        if (window == NULL)
        {
            printf("Failed to create GLFW window\n");
            glfwTerminate();
            return window;
        }
        glfwMakeContextCurrent(window);

        glfwSetFramebufferSizeCallback(window, framebufferSize_callback);

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
    void processInput(GLFWwindow *window, Scene *scene)
    {
        // Cameras
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        {
            scene->ToggleActiveCamera(0);

        }
        else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        {
            scene->ToggleActiveCamera(1);
        }
        else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        {
            scene->ToggleActiveCamera(2);
        }
        // Display mode
        else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        }
        else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        // Close
        else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }
    }
}