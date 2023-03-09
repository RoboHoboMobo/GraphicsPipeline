#include "VertexArray.h"

VertexArray::VertexArray()
  : m_rendererId{}
{
  glGenVertexArrays(1, &m_rendererId);
}

VertexArray::~VertexArray()
{
  glDeleteVertexArrays(1, &m_rendererId);
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
  bind();

  vb.bind();
  auto elements = layout.getElements();

  unsigned int offset{};

  for (size_t i = 0; i < elements.size(); ++i) {
    auto element = elements[i];
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, element.count, element.type,
                          element.isNormalized ? GL_TRUE : GL_FALSE,
                          layout.getStride(), reinterpret_cast<const void*>(offset));

    offset += element.count * sizeof(element.type);
  }
}

void VertexArray::bind() const
{
  glBindVertexArray(m_rendererId);
}

void VertexArray::unbind() const
{
  glBindVertexArray(0);
}
