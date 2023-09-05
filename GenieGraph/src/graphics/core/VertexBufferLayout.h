#pragma once

#include <GL/glew.h>
#include <vector>


/*  Defines the layout for the Vertex Buffer Object (VBO) within the Vertex Array Object (VAO)
*/


struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type) {
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		return 0;
	}
};

class VertexBufferLayout {

private:
	std::vector<VertexBufferElement> m_Elements;
	std::vector<int> m_Stride;

public:
	VertexBufferLayout()
		:m_Stride(0) {}


	template<typename T>
	void Push(unsigned int count) {
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count) {
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });  // Normalization hard coded
		m_Stride.push_back(VertexBufferElement::GetSizeOfType(GL_FLOAT) * count);
	}

	template<>
	void Push<unsigned int>(unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });  // Normalization hard coded
		m_Stride.push_back(VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count);
	}

	template<>
	void Push<unsigned char>(unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });  // Normalization hard coded
		m_Stride.push_back(VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count);
	}

	inline const std::vector<VertexBufferElement> GetElements() const& { return m_Elements; };
	inline unsigned int GetStride(int i) const { return m_Stride[i]; };
};