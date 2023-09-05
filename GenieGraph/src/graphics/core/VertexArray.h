#pragma once

#include <iostream>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

/*  A Vertex Array Object (or VAO) is an object that describes 
how the vertex attributes are stored in a Vertex Buffer Object (or VBO).
This means that the VAO is not the actual object storing the vertex data,
but the descriptor of the vertex data.
*/

class VertexBufferLayout;

class VertexArray { 
private:
	unsigned int m_RendererID;
	unsigned int last_offset = 0;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, int layout_pos);

	void Bind() const;
	void Unbind() const;
};