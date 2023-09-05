#include "IndexBuffer.h"


IndexBuffer::IndexBuffer() {}

IndexBuffer::~IndexBuffer() {
    std::cout << "Deleting IBO" << std::endl;
    glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Create(const void* data, unsigned int size) {
    m_Count = size;
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW); //GL_STATIC can be switched to dynamic for efficiency when modifying verticies
}

void IndexBuffer::Update(const void* data, unsigned int size) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW); //GL_STATIC can be switched to dynamic for efficiency when modifying verticies
}


void IndexBuffer::Bind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


