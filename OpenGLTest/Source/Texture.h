
//Texture.h
#pragma once
#include "Renderer.h"

class Texture
{
public:
	Texture(const std::string& filePath);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
private:
	unsigned int rendererID;
	std::string filePath;
	int width, height, bpp;//bbp mean bits per pixel
	unsigned char* localBuffer;
};

