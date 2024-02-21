#include "VertexArray.h"
#include <RenderSystem/RenderSystem.h>
#include <iostream>
#include <cstddef>

namespace dark {

	VertexArray::VertexArray()
	{
		
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::Generate()
	{
		glGenBuffers(1, &m_RendererID);
	}

	void VertexArray::Create()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	/**
	 * Buffer of the Vertex Attribute layout
	 */
	void VertexArray::AddBuffer(IndexBuffer& ib, VertexBuffer& vb, const VertexBufferLayout& layout)
	{
		
		std::cout << "[Create] Vertex Array" << std::endl;
		
		glVertexArrayVertexBuffer(m_RendererID, 0, vb.getBufferTarget(), 0, sizeof(Model3D::Vertex));
		/**
		 *	Describe the memory layout of our incoming VertexBufferElements
		 */
		const auto& elements = layout.getElements();

		// TODO - This is a hard-coded setup
		size_t offsets[3] = { offsetof(Model3D::Vertex, position), offsetof(Model3D::Vertex, color), offsetof(Model3D::Vertex, normal) };
		if (elements.size() != 3) {
			throw std::runtime_error("Number of offsets do not match the vertex shader's attribute count.");
		}

		std::cout << "Element Count: " << elements.size() << std::endl;
		for (unsigned int i = 0; i < elements.size(); i++)
		{
			const auto& element = elements[i];
			/**
			* DSA Support 
			* Associating the vertex attribute to each binding point (0) and enable them.
			*/
			glVertexArrayAttribFormat(m_RendererID, i, element.count, element.type, element.normalized, offsets[i]);
			glVertexArrayAttribBinding(m_RendererID, i, 0);
			glEnableVertexArrayAttrib(m_RendererID, i);

		}
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

}