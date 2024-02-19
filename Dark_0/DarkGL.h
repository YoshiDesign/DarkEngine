#pragma once
#include "Window.h"
#include <RenderSystem/RenderSystem.h>
#include <GameSystem/Creative/AppObject.h>
#include <GameSystem/Periph/KeyboardController.h>
#include <RenderSystem/Camera/Camera.h>
#include <RenderSystem/GUI/MainGui.h>

namespace dark {
	class DarkGL {

	public:
		DarkGL();
		~DarkGL();

		DarkGL(const DarkGL&) = delete;
		DarkGL& operator=(const DarkGL&) = delete;

		void Setup();
		void display(Window& window, double currentTime);
		int run();
		void updateCamera(float frameTime);
		void updateCamera(float frameTime, AppObject& viewerObject, Camera& camera);

	private:
		Window window;
		RenderSystem renderer;
		static constexpr int WIDTH = 960;
		static constexpr int HEIGHT = 540;
		float aspect{ (float)WIDTH / (float)HEIGHT };

		AppObject::Map appObjects;
		AppObject viewerObject{ AppObject::createAppObject() };
		KeyboardController cameraController{};
		Camera camera{};
		MainGui gui;

	};
}