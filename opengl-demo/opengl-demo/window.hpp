#pragma once
#include "includes.hpp"

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
    // Display mode:
    // 1 - filled polygons
    // 2 - wireframe of polygons
    void processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        }
        else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
    }
}