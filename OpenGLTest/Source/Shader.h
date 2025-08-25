
//Shader.h
#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

struct ShaderSource
{
	std::string vertexShaderSource;
	std::string fragmentShaderSource;
};

class Shader
{
public:
	Shader(const std::string& filePath);
	~Shader();

	ShaderSource ParseShaderSource(const std::string& fileName);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	int CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

	void Bind() const;
	void Unbind() const;
	
	void SetUniform1b(const std::string& name, bool value);
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
	int GetUniformLocation(const std::string& name);

	unsigned int rendererID;
	std::string filePath;
	std::unordered_map<std::string, int> uniformLocationsMap;
};

