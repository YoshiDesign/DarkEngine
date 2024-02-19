#pragma once
#include "Test.h"
#include <memory>
#include <RenderSystem/RenderSystem.h>
#include <RenderSystem/Data/VertexBuffer.h>
#include <RenderSystem/Data/VertexBufferLayout.h>
#include <RenderSystem/Data/VertexArray.h>
#include <RenderSystem/Shaders/Shader.h>
#include <RenderSystem/Texture/Texture.h>

namespace test {

	class TestTexture2D : public Test {
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float dt) override;
		void OnRender() override;
		void OnImguiRender() override;

	private:
		std::unique_ptr <VertexBuffer> m_VertexBuffer;
		std::unique_ptr <VertexArray>  m_VertexArray;
		std::unique_ptr <IndexBuffer>  m_IndexBuffer;
		std::unique_ptr <dark::Shader> m_Shader;
		std::unique_ptr <Texture>	   m_Texture;
		glm::mat4 m_Proj;
		glm::mat4 m_View;
		glm::vec3 m_TranslationA, m_TranslationB;
	};
	
}