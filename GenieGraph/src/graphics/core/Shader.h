#pragma once

#include <GL/glew.h>

#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>

#include "glm/glm.hpp";
#include "glm/gtc/matrix_transform.hpp"


struct ShaderProgramSource {
	std::string VertexSource; // Stores whole vertex shader as a single string
	std::string FragmentSource; // Stores whole fragment shader as a single string
};

class Shader {
private:

	std::string m_Filepath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, unsigned int> m_UniformLocationCache; // Stores uniform location after first search

public:

	Shader(const std::string& filename);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Set Uniforms
	void SetUniform4f(const std::string& name, float v0, float v1, float f2, float f3); // Replace with vectors
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix); // Replace with vectors

private:
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	ShaderProgramSource ParseShader(const std::string& filepath);

	int GetUniformLocation(const std::string& name);
};