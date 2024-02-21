#pragma once
#include <GameSystem/Creative/Model3D.h>

namespace dark {
	class VertexBuffer {

	public:

		VertexBuffer(/*const void* data, unsigned int size*/);
		~VertexBuffer();
		void Generate();
		void Create(); // DSA
		void Bind();
		void UpdateData(const void* data, unsigned int size);
		void Unbind() const;
		GLuint getBufferTarget() { return m_RendererID; }

	private:
		// The 'name' of our buffer. This needs to be an array of n unsigned int's if we're allocating n vertex buffers from here. Right now it's just 1
		GLuint m_RendererID;

	};
}