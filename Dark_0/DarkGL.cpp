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

        window.InitWindow(WIDTH, HEIGHT, "Dark_0");
        if (!glewInit() == GLEW_OK) {
        	throw std::runtime_error("Glew is not ok!");
        }

        std::cout << glGetString(GL_VERSION) << std::endl;

    }

    void DarkGL::display(Window& window, double currentTime)
    {

    }

    int DarkGL::run()
    {

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 10; j++) {

                auto obj = AppObject::createAppObject(/*TODO Implement textures*/);
                obj.model = Model3D::createModelFromFile("resource/3D/Enemy_1.obj");
                obj.transform.translation.z = -15.0f;
                obj.transform.translation.x = -15.0f * j;
                obj.transform.translation.y = 15.0f * i;
                //obj.transform.scale = { i + j, i + j, i + j };
                appObjects.emplace(obj.getId(), std::move(obj));

            }
        }

        renderer.ShaderInit();
        renderer.Generate();

        FrameContent frameContent { camera, appObjects };

        while (!window.shouldClose())
        {

            updateCamera(glfwGetTime(), viewerObject, camera);
            renderer.Clear();
            renderer.Draw(frameContent);

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