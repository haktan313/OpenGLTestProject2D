
//Shader.cpp
#include "Shader.h"
#include <GL/glew.h>
#include "Renderer.h"
#include "fstream"
#include "sstream"
#include <iostream>

Shader::Shader(const std::string& filePath) : filePath(filePath), rendererID(0) 
{
	ShaderSource shaderSource = ParseShaderSource(filePath);
	rendererID = CreateShader(shaderSource.vertexShaderSource, shaderSource.fragmentShaderSource);
}

Shader::~Shader() 
{
	GLDebugCall(glDeleteProgram(rendererID));
}

ShaderSource Shader::ParseShaderSource(const std::string& fileName)
{
	std::ifstream stream(fileName);

	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};
	ShaderType shaderType = ShaderType::NONE;

	std::string line;
	std::stringstream ss[2];

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				std::cout << "Vertex Shader found!" << std::endl;
				shaderType = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				std::cout << "Fragment Shader found!" << std::endl;
				shaderType = ShaderType::FRAGMENT;
			}
			else
			{
				std::cout << "Unknown shader type!" << std::endl;
				shaderType = ShaderType::NONE;
			}
		}
		else
		{
			ss[(int)shaderType] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	GLDebugCall(glShaderSource(id, 1, &src, nullptr));
	GLDebugCall(glCompileShader(id));
	if (!CheckGLError(id, GL_COMPILE_STATUS))
	{
		GLDebugCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

int Shader::CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
	unsigned int program = glCreateProgram();
	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	GLDebugCall(glAttachShader(program, vertexShader));
	GLDebugCall(glAttachShader(program, fragmentShader));

	GLDebugCall(glLinkProgram(program));
	if (!CheckGLError(program, GL_LINK_STATUS))
	{
		GLDebugCall(glDeleteProgram(program));
		return 0;
	}

	GLDebugCall(glValidateProgram(program));
	if (!CheckGLError(program, GL_VALIDATE_STATUS))
	{
		return 0;
	}

	GLDebugCall(glDeleteShader(vertexShader));
	GLDebugCall(glDeleteShader(fragmentShader));

	return program;
}

void Shader::Bind() const 
{
	GLDebugCall(glUseProgram(rendererID));
}

void Shader::Unbind() const 
{
	GLDebugCall(glUseProgram(0));
}

void Shader::SetUniform1b(const std::string& name, bool value)
{
	glUniform1i(GetUniformLocation(name), (int)value);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::GetUniformLocation(const std::string& name)
{
	if(uniformLocationsMap.find(name) != uniformLocationsMap.end())
	{
		return uniformLocationsMap[name];
	}
	int colorLocation = glGetUniformLocation(rendererID, name.c_str());
	if (colorLocation == -1)
	{
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	}
	uniformLocationsMap[name] = colorLocation;
	return colorLocation;
}

