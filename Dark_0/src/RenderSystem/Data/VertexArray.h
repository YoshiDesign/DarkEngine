#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

namespace dark {

	class VertexArray {

	public:

		VertexArray();
		~VertexArray();

		void AddBuffer(IndexBuffer& ib, VertexBuffer& vb, const VertexBufferLayout& layout);
		void Bind();
		void Unbind();

	private:

		GLuint m_RendererID;

	};

}