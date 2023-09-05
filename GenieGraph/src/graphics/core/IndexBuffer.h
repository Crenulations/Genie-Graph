#pragma once
#include <GL/glew.h>
#include <iostream>

/*  An Index Buffer Object (IBO) stores sets of 3 vertex buffer elements (verticies) 
* which OpenGL uses to draw triangles.
*/

class IndexBuffer {
private:
	unsigned int m_RendererID;
	unsigned int m_Count;  // Number of indicies
public:
	IndexBuffer();
	~IndexBuffer();

	void Create(const void* data, unsigned int size);
	void Update(const void* data, unsigned int size);

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; };
};