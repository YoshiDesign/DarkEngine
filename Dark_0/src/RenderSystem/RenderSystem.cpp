#include <RenderSystem/RenderSystem.h>
#include <RenderSystem/Camera/Camera.h>
#include <iostream>

namespace dark {

	void GLClearError()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	bool GLLogCall(const char* function, const char* file, int line)
	{
		while (GLenum error = glGetError())
		{
			std::cout << "[OpenGL Error] (" << error << "): " << function << ":" << line << std::endl;
			return false;
		}

		return true;

	}

	void RenderSystem::Clear() const
	{
		GLCall(glClearColor(0.0f, 1.0f, 0.0f, 1.0));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void RenderSystem::ShaderInit()
	{
		shaderSystem.AddShader("resource/shaders/shader0.shader", "Shader_Zero");
		//shaderSystem.AddShader("resource/shaders/01_Simple_3D.shader", "GreenShader");
		
	}

	void RenderSystem::CreateNamedUniformBlock()
	{
		ubo.CreateNamedUniformBlock("Transforms", shaderSystem.GetID("BlueShader"), 3);
	}

	void RenderSystem::BufferInit()
	{

		// Gen VA
		VertexArray va;
		// Gen VB
		VertexBuffer vb;
		// Gen IB
		IndexBuffer ib;

		// Construct vertex shader attributes
		VertexBufferLayout layout;
		layout.PushVertex(sizeof(Model3D::Vertex));

		// Bind and add VA -- Create our vertex attribute locations
		va.AddBuffer(ib, vb, layout);
	}

	void RenderSystem::Draw(FrameContent& frameContent)
	{
		// Probably doesn't need to go into the loop
		shaderSystem.Bind("Shader_Zero");

		for (auto& obj : frameContent.appObjects) {
			// Write model vertex data to the vertex buffer
			vb.UpdateData(obj.second.model->getVerticesv(), obj.second.model->getNumVertices());
			ib.UpdateData(obj.second.model->getIndicesv(), obj.second.model->getNumIndices());
			GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
		}

		// GLCall(glDrawArrays(GL_POINTS, 0, 1));
	}

}