#include "IndexBuffer.h"
#include <iostream>

IndexBuffer::IndexBuffer()
{
    std::cout << "Gen Index Buffer" << std::endl;
    glGenBuffers(1, &m_RendererID);
}

void IndexBuffer::UpdateData(const unsigned int* data, unsigned int count)
{
    m_count = count;
    // This could cause incompat on certains platforms if !true
    // ASSERT(sizeof unsigned int == sizeof GLuint)
    //std::cout << "Num indices: " << count << std::endl;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
