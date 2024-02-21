#pragma once


namespace dark {

	class UBO {
	public:
		UBO();
		~UBO();

		void CreateNamedUniformBlock(const char* blockName, unsigned int program, unsigned int num);
		void FreeUniformBlockBuffer(); // Only use where swapping/destroying buffers during lifespan of the derived class, the destructor does the same thing
		void Generate();
		void Create();
		void Bind();
		void Allocate();
		void Unbind();

		inline unsigned char* getBuffer() { return blockBuffer; }
		inline int getBlockSize() { return blockSize; }
		inline unsigned int getID() { return m_uboId; }
		
		unsigned int m_uboId;
		unsigned int indices[3];
		int offsets[3];

	private:
		unsigned char* blockBuffer{ nullptr };
		int blockSize;
		unsigned int ubo_index;
	};

}