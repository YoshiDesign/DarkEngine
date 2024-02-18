#include "RenderSystem.h"
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

	void RenderSystem::Draw() 
	{
		shaderSystem.Bind("Shader_Zero");
		GLCall(glDrawArrays(GL_POINTS, 0, 1));
	}

}