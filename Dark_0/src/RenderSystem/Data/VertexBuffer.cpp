#include "VertexBuffer.h"

namespace dark {

    VertexBuffer::VertexBuffer(/*const void* data, unsigned int size */)
    {
        glCreateBuffers(1, m_RendererID);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, m_RendererID);
    }

    void VertexBuffer::UpdateData(const void* data, unsigned int size)
    {
        //std::cout << "Num Vertices: " << size << std::endl;
        glBufferData(GL_ARRAY_BUFFER, size * sizeof(Model3D::Vertex), data, GL_STATIC_DRAW);
    }

    void VertexBuffer::Bind() const
    {
        glCreateBuffers(GL_ARRAY_BUFFER, m_RendererID);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

}