
//VertexBufferLayout.h
#pragma once
#include <vector>
#include <GL/glew.h>
#include <stdexcept>

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;//components like 2 for (x, y) or 4 for (r, g, b, a)
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		default:
			return 0;
		}
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> vertexBufferElements;
	unsigned int stride;//how far to go to the next vertex attribute
public:
	VertexBufferLayout() : stride(0) {}

	template <typename T>
	void Push(unsigned int count)//if value of T is not matched with any of the types below, it will throw an error
	{
		std::runtime_error(false);
		//static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		vertexBufferElements.push_back({ GL_FLOAT, count, GL_FALSE});
		stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		vertexBufferElements.push_back({ GL_UNSIGNED_INT, count,  GL_FALSE});
		stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		vertexBufferElements.push_back({ GL_UNSIGNED_BYTE,count,  GL_TRUE});
		stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement>& GetElements() const { return vertexBufferElements; }
	inline unsigned int GetStride() const { return stride; }
};

