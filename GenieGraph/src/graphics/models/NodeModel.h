#pragma once

#include "../core/VertexArray.h"
#include "../core/IndexBuffer.h"
#include "../core/Shader.h"
#include "glm/glm.hpp";
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include "../util/Basic.h"

class NodeModel {
private:

	VertexBufferLayout layout;
	VertexBuffer vbo;
	VertexBuffer vbo_color;
	IndexBuffer ibo;
	VertexArray vao;
	Shader shader;

public:
	unsigned int vert_count = 0;
	unsigned int edge_count = 0;

	NodeModel();
	~NodeModel();
	void CreateVAO(std::vector< float > loc_data, std::vector< float > color_data);
	void CreateIBO(const void* edge_data, unsigned int count);

	void ChangeMVPUniform(glm::mat4 MVP);
	void SwapLocationBuffer(const void* loc_data);
	void SwapEdgeBuffer(const void* edge_data);
	void SwapColorBuffer(const void* color_data);
	void Bind();
};