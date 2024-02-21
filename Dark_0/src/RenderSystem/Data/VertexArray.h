#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

namespace dark {

	class VertexArray {

	public:

		VertexArray();
		~VertexArray();
		void Generate();
		void AddBuffer(IndexBuffer& ib, VertexBuffer& vb, const VertexBufferLayout& layout);
		void Bind();
		void Create();
		void Unbind();
		GLuint getBufferTarget() { return m_RendererID; }

	private:

		GLuint m_RendererID;

	};

}