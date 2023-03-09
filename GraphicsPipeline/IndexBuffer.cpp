#include "IndexBuffer.h"

#include "Renderer.h"

#include <cassert>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int num)
  : m_rendererId{}
  , m_count{num}
{
  assert(sizeof(unsigned int) == sizeof(GLuint));

  glGenBuffers(1, &m_rendererId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, num * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
  glDeleteBuffers(1, &m_rendererId);
}

void IndexBuffer::bind() const
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
}

void IndexBuffer::unbind() const
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
