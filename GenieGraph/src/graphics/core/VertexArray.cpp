#include "VertexArray.h"


VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_RendererID);
}
VertexArray::~VertexArray() {
	std::cout << "Deleting VAO" << std::endl;
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, int layout_pos) {
	
	Bind();
	vb.Bind();

	const auto& elements = layout.GetElements();
	//unsigned int offset = 0;

	//for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[layout_pos];
		glEnableVertexAttribArray(layout_pos);
		glVertexAttribPointer(layout_pos, element.count, element.type, element.normalized, layout.GetStride(layout_pos), (const void*)last_offset);
		last_offset += (element.count - 3) * VertexBufferElement::GetSizeOfType(element.type);
	//}
}

void VertexArray::Bind() const {
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);
}
