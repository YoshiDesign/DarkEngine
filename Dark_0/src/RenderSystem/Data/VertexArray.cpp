#include "VertexArray.h"
#include <RenderSystem/RenderSystem.h>
#include <iostream>


VertexArray::VertexArray()
{
	std::cout << "Gen Vertex Array" << std::endl;
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

/**
 * Buffer of the Vertex Attribute layout
 */
void VertexArray::AddBuffer(IndexBuffer& ib, VertexBuffer& vb, const VertexBufferLayout& layout)
{
	// Bind the Vertex Array
	Bind();
	// Bind the Vertex Array's Buffer
	vb.Bind();
	ib.Bind();
	// Describe the memory layout of our incoming VertexBufferElements
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	//std::cout << "Element Count: " << elements.size() << std::endl;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];

		glEnableVertexAttribArray(i);
		// TODO - Replace glVertexAttribPointer with a less shitty function
		// See: https://stackoverflow.com/questions/37972229/glvertexattribpointer-and-glvertexattribformat-whats-the-difference
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
		offset += element.count * sizeof(GLfloat);

	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
