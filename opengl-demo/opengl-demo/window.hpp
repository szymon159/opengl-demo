#pragma once
#include "includes.hpp"

#include "scene.hpp"

namespace Window
{
    void framebufferSize_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    GLFWwindow* createWindow()
    {
        GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
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
    }
}