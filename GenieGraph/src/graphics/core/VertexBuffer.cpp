#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() {
}

VertexBuffer::~VertexBuffer() {
    std::cout << "Deleting VBO " << m_RendererID << std::endl;
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Create(const void* data, unsigned int size) {
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW); //GL_STATIC can be switched to dynamic for efficiency when modifying verticies
}

void VertexBuffer::Update(const void* data, unsigned int size) {
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW); //GL_STATIC can be switched to dynamic for efficiency when modifying verticies
}

void VertexBuffer::Bind() const{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
