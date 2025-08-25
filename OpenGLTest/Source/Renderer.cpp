
//Renderer.cpp
#include <iostream>
#include "Renderer.h"

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}
bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}
bool CheckGLError(const unsigned int shader, const unsigned int pname)
{
	int result;
	glGetShaderiv(shader, pname, &result);
	if (result == GL_FALSE)
	{
		std::string pnameStr;

		switch (pname)
		{
		case GL_COMPILE_STATUS:
			pnameStr = "Failed to compile ";
			break;
		case GL_LINK_STATUS:
			pnameStr = "Failed to link ";
			break;
		case GL_VALIDATE_STATUS:
			pnameStr = "Failed to validate ";
			break;
		}

		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

		char* message = /*new char[length]*/(char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(shader, length, &length, message);

		std::cout << pnameStr << (shader == GL_VERTEX_SHADER ? "vertex shader!" : "fragment shader!") << std::endl;
		std::cout << message << std::endl;

		//delete[] message;
		return false;
	}
	return true;
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const
{
	shader.Bind();
	vertexArray.Bind();
	indexBuffer.Bind();
	GLDebugCall(glDrawElements(GL_TRIANGLES, indexBuffer.GetCount() , GL_UNSIGNED_INT, nullptr));
}
