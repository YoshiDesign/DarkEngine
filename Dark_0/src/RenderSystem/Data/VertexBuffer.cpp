#include "VertexBuffer.h"

namespace dark {

    VertexBuffer::VertexBuffer(/*const void* data, unsigned int size */)
    {
        
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }

    // LEGACY SUPPORT
    void VertexBuffer::Generate()
    {
        glGenBuffers(1, &m_RendererID);
    }

    void VertexBuffer::Create()
    {
        glCreateBuffers(1, &m_RendererID);
    }

    void VertexBuffer::UpdateData(const void* data, unsigned int size)
    {
        //std::cout << "Num Vertices: " << size << std::endl;
        // glBufferData(GL_ARRAY_BUFFER, size * sizeof(Model3D::Vertex), data, GL_STATIC_DRAW);
        glNamedBufferData(m_RendererID, size * sizeof(Model3D::Vertex), data, GL_STATIC_DRAW);
        // glNamedBufferStorage(getBufferTarget(), size * sizeof(Model3D::Vertex), data, GL_DYNAMIC_STORAGE_BIT);

    }

    void VertexBuffer::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

}