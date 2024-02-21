#pragma once
#include <dark_core.h>
namespace dark {
	class IndexBuffer {

	public:

		IndexBuffer();
		~IndexBuffer();
		void Generate();
		void Bind();
		void Create();
		void Unbind() const;
		void UpdateData(const unsigned int* data, unsigned int count);
		inline unsigned int GetCount() const { return m_count; }
		GLuint getBufferTarget() { return m_RendererID; }

	private:
		GLuint m_RendererID;
		unsigned int m_count;

	};
}