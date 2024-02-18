#pragma once
#include "Window.h"
#include <RenderSystem/RenderSystem.h>

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

	private:
		Window window;
		RenderSystem renderer;
		static constexpr int WIDTH = 960;
		static constexpr int HEIGHT = 540;
	};
}