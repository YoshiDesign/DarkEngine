#pragma once
#include "dark_core.h"
#include <RenderSystem/Shaders/Shader.h>
#include <RenderSystem/FrameContent.h>
#include <RenderSystem/Data/IndexBuffer.h>
#include <RenderSystem/Data/VertexArray.h>
#include <RenderSystem/Data/VertexBuffer.h>
#include <RenderSystem/Data/VertexBufferLayout.h>
#include <RenderSystem/Data/UBO.h>

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
		void Draw(FrameContent& frameContent);
		void Generate();
		void BufferInit();
		void UBOInit();
		void ShaderInit();
		void CreateNamedUniformBlock();
		UBO& getUBO() { return ubo; }
		// void Draw(VertexArray& va, VertexBuffer& vb, IndexBuffer& ib, ShaderSystem& shaderSystem, FrameContent& frame_content) const;
	private:
		Shader shaderSystem;
		VertexArray va;
		VertexBuffer vb;
		IndexBuffer ib;
		UBO ubo;
		unsigned int m_uboID;
	};
}
