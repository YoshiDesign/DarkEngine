#pragma once
#include "dark_core.h"
#include <RenderSystem/Shaders/Shader.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

namespace dark {
	void GLClearError();

	bool GLLogCall(const char* function, const char* file, int line);

	class RenderSystem {
	public:
		void Clear() const;
		void Draw();
		void ShaderInit();
		// void Draw(VertexArray& va, VertexBuffer& vb, IndexBuffer& ib, ShaderSystem& shaderSystem, FrameContent& frame_content) const;
	private:
		Shader shaderSystem;
		unsigned int m_uboID;
	};
}
