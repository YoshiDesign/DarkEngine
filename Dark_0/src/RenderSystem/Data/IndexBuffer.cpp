#include "IndexBuffer.h"
#include <iostream>
namespace dark {

    IndexBuffer::IndexBuffer()
    {

    }

    // LEGACY SUPPORT < OpenGL3.x
    void IndexBuffer::Generate()
    {
        glGenBuffers(1, &m_RendererID);
    }
    
    // Used with OpenGL4.x DSA
    void IndexBuffer::Create()
    {
        glCreateBuffers(1, &m_RendererID);
    }

    void IndexBuffer::UpdateData(const unsigned int* data, unsigned int count)
    {
        m_count = count;

        // This could cause incompat on certains platforms if !true
        // ASSERT(sizeof unsigned int == sizeof GLuint)

        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
        glNamedBufferData(m_RendererID, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
        //glNamedBufferStorage(getBufferTarget(), count * sizeof(unsigned int), data, GL_MAP_WRITE_BIT);
        
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }

    void IndexBuffer::Bind()
    {
        std::cout << "[Bind] Index Buffer" << std::endl;
        //glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

        std::cout << "Gen Index Buffer" << std::endl;
        
    }

    void IndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

}