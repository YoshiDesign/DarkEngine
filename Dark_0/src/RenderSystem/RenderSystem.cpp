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

	void RenderSystem::Generate()
	{

		BufferInit();

		ubo.Create();
		ubo.CreateNamedUniformBlock("Transforms", shaderSystem.GetID("Shader_Zero"), 3);
		ubo.Bind();
		ubo.Allocate();

		shaderSystem.Bind("Shader_Zero");
	}

	void RenderSystem::Clear() const
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void RenderSystem::ShaderInit()
	{
		shaderSystem.AddShader("resource/shaders/shader1.shader", "Shader_Zero");
		//shaderSystem.AddShader("resource/shaders/01_Simple_3D.shader", "GreenShader");
		
	}

	void RenderSystem::BufferInit()
	{

		// Create/Bind the holy trinity via DSA functions
		va.Create();
		ib.Create();
		vb.Create();
		va.Bind();
		vb.Bind();
		ib.Bind();

		// Construct vertex shader attributes
		VertexBufferLayout layout;
		layout.PushVertex(sizeof(Model3D::Vertex));

		// Bind and add VA -- Create our vertex attribute locations
		va.AddBuffer(ib, vb, layout);
	}

	void RenderSystem::Draw(FrameContent& frameContent)
	{
		/**
		* TODOs - If ubo.getBlockSize() ever changes we need to call UBO::Allocate() again
		*		- Optimization: Currently using 3 mat4's in our uniform block while
		*		  2 of its elements are updated per frame and 1 is updated per object; however
		*		  I'm overwriting the entire uniform block for every object. Relieving the 
		*		  uniform block of the model matrix would remove glMap/unmap from the appObject loop.
		*		  Removing each object's model matrix to a different uniform could be helpful.
		*		- Optimization: vb.UpdateData and ib.UpdateData both use glBufferData which
		*		  reallocates the entire buffer before writing updates which can be inefficient.
		*		- Certain assertions could be helpful, such as assuring OpenGL that all of the 
		*		  data being copied into the uniform block is the correct size.
		*/
		
		*((glm::mat4*)(ubo.getBuffer() + ubo.offsets[0])) = frameContent.camera.getView();
		*((glm::mat4*)(ubo.getBuffer() + ubo.offsets[1])) = frameContent.camera.getProjection();

		for (auto& obj : frameContent.appObjects) {

			void* ptr = glMapNamedBuffer(ubo.getID(), GL_WRITE_ONLY | GL_MAP_INVALIDATE_BUFFER_BIT);

			// Point to the model matrix of our uniform block
			*((glm::mat4*)(ubo.getBuffer() + ubo.offsets[2])) = obj.second.transform._mat4();

			// Write the new uniform block values
			memcpy(ptr, ubo.getBuffer(), ubo.getBlockSize());

			glUnmapNamedBuffer(ubo.getID());

			glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo.getID());

			// Write model vertex data to the vertex buffer
			vb.UpdateData(obj.second.model->getVerticesv(), obj.second.model->getNumVertices());
			ib.UpdateData(obj.second.model->getIndicesv(), obj.second.model->getNumIndices());

			// getNummVertices is the number of unique vertices
			GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));  // nullptr because the index buffer is already bound
		}

		//GLCall(glDrawArrays(GL_POINTS, 0, 1));
	}

}