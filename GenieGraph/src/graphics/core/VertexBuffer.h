#pragma once
#include <GL/glew.h>
#include <iostream>

class VertexBuffer {

/*  A Vertex Buffer Object (or VBO) stores vertex data such as position, normal vector, color, etc.
*/

private:
	unsigned int m_RendererID;
public:
	VertexBuffer();
	~VertexBuffer();

	void Create(const void* data, unsigned int size);
	void Update(const void* data, unsigned int size);

	void Bind() const;
	void Unbind() const;
};