#pragma once
#include "glm/glm.hpp";
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>  // copy()
#include <iterator>   // istream_iterator, back_inserter
#include <string>

#include "../core/IndexBuffer.h"
#include "../core/VertexArray.h"
#include "../core/Shader.h"

class Model {
protected:
	VertexBuffer vbo;
	VertexArray vao;
	VertexBufferLayout layout;
	IndexBuffer ibo;
	Shader shader; // Should become material eventually 
public:
	Model(const std::string& obj_filepath, const std::string& shader_filepath);
	~Model();

	void ChangeMVPUniform(glm::mat4 MVP);
	void ChangeColorUniform(float r, float g, float b, float a);

	void Bind();

	VertexArray* get_vao();
	IndexBuffer* get_ibo();
	Shader* get_shader();

	void ParseModelFile(const std::string& filepath);
	void MakeUnitCube();
	void MakeSquare();
};