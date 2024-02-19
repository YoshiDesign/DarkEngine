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

    void DarkGL::updateCamera(float frameTime, AppObject& viewerObject, Camera& camera)
    {
        cameraController.moveInPlaneXZ(window.getGLFWwindow(), frameTime, viewerObject);
        camera.setViewYXZ(viewerObject.transform.translation + glm::vec3(0.f, 0.f, 0.f), viewerObject.transform.rotation + glm::vec3());
        camera.setPerspectiveProjection(glm::radians(50.f), aspect, 2.0f, 500.f);
    }

}