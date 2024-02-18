#include "DarkGL.h"
#include <iostream>
#include <chrono>

// Darknews
namespace dark {
    DarkGL::~DarkGL()
    {
    }
    DarkGL::DarkGL()
    {
        Setup();
    }

    void DarkGL::Setup()
    {

        window.InitWindow(WIDTH, HEIGHT, "Darkness");
        if (!glewInit() == GLEW_OK) {
        	throw std::runtime_error("Glew is not ok!");
        }

        std::cout << glGetString(GL_VERSION) << std::endl;

    }

    void DarkGL::display(Window& window, double currentTime)
    {
        renderer.Clear();
        renderer.Draw();
    }

    int DarkGL::run()
    {
        // Compile, bind and select shaders.
        renderer.ShaderInit();

        while (!window.shouldClose())
        {
            display(window, glfwGetTime());
            // Swap front and back buffers
            glfwSwapBuffers(window.getGLFWwindow());

            // Poll for and process events
            glfwPollEvents();
        }

        glfwDestroyWindow(window.getGLFWwindow());
        glfwTerminate();

        return 0;

    }
}