#include "VertexBufferLayout.h"

void VertexBufferLayout::push(unsigned int count, float)
{
  m_elements.push_back({GL_FLOAT, count, false});
  m_stride += count * sizeof(GLfloat);
}

void VertexBufferLayout::push(unsigned int count, unsigned int)
{
  m_elements.push_back({GL_UNSIGNED_INT, count, false});
  m_stride += count * sizeof(GLuint);
}
