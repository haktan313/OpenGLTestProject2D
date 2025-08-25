
//IndexBuffer.cpp
#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : countRef(count)
{
	GLDebugCall(glGenBuffers(1, &rendererID));
	GLDebugCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
	GLDebugCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER,/*4*2*sizeof(float) sizeof(positions)*/count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLDebugCall(glDeleteBuffers(1, &rendererID));
}

void IndexBuffer::Bind() const
{
	GLDebugCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
}

void IndexBuffer::Unbind() const
{
	GLDebugCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
