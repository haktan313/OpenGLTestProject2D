
//VertexBuffer.cpp
#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLDebugCall(glGenBuffers(1, &rendererID));
	GLDebugCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
	GLDebugCall(glBufferData(GL_ARRAY_BUFFER,/*4*2*sizeof(float) sizeof(positions)*/size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLDebugCall(glDeleteBuffers(1, &rendererID));
}

void VertexBuffer::Bind() const
{
	GLDebugCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
}

void VertexBuffer::Unbind() const
{
	GLDebugCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
