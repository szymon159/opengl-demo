#include "includes.h"

// TODO: Move to another file when refactoring
int initializeGLFW()
{
    if (!glfwInit())
        return 0;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return 1;
}


int main()
{
    if (!initializeGLFW())
        return EXIT_FAILURE;

	return EXIT_SUCCESS;
}