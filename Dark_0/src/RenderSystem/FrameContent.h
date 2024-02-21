#pragma once
#include <RenderSystem/Camera/Camera.h>
#include <GameSystem/Creative/AppObject.h>
#include <vector>


namespace dark {

	struct FrameContent {
		Camera& camera;
		AppObject::Map& appObjects;
	};

}