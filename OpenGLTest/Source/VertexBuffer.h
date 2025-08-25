
//VertexBuffer.h
#pragma once

class VertexBuffer
{
private:
	unsigned int rendererID;
public:
	VertexBuffer(const void* data, unsigned int size); // size is the size of the data in bytes like sizeof(positions)
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};

