
//Renderer.h
#pragma once
#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define DEBUGBREAKPOINT(x) if(!(x)) __debugbreak()
#define GLDebugCall(x) GLClearError();\
	x;\
	DEBUGBREAKPOINT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

bool CheckGLError(const unsigned int shader, const unsigned int pname);

class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;
};