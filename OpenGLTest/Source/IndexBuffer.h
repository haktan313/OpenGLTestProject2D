
//IndexBuffer.h
#pragma once

class IndexBuffer
{
private:
	unsigned int rendererID;
	unsigned int countRef;// Number of indices
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	inline unsigned int GetCount() const { return countRef; }
};

