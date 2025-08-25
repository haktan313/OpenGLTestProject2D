
//VertexArray.cpp
#include "VertexArray.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
	GLDebugCall(glGenVertexArrays(1, &rendererID));
}

VertexArray::~VertexArray()
{
	GLDebugCall(glDeleteVertexArrays(1, &rendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();

	const auto& elements = layout.GetElements();
	unsigned int offset = 0;

	for(unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLDebugCall(glEnableVertexAttribArray(i));
		GLDebugCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	GLDebugCall(glBindVertexArray(rendererID));
}

void VertexArray::Unbind() const
{
	GLDebugCall(glBindVertexArray(0));
}