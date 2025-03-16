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

        auto ship = AppObject::createAppObject(/*TODO Implement textures*/);
        ship.model = Model3D::createModelFromFile("resource/3D/ship.obj"); 
        appObjects.emplace(ship.getId(), std::move(ship));

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 10; j++) {

                auto tri = AppObject::createAppObject(/*TODO Implement textures*/);
                tri.model = Model3D::createModelFromFile("resource/3D/triangle.obj");
                tri.transform.translation.z = -2.0f * i;
                tri.transform.translation.x = -2.0f * j;
                //obj.transform.translation.y = 15.0f * i;
                //obj.transform.scale = { i + j, i + j, i + j };
                appObjects.emplace(tri.getId(), std::move(tri));
                
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