#pragma once

#include <vector>

#include <GL/glew.h>

struct VertexBufferElement {
  unsigned int type;
  unsigned int count;
  bool isNormalized;
};

class VertexBufferLayout {
public:
  VertexBufferLayout()
    : m_stride{}
  {
  }

  template<typename T>
  void push(unsigned int count)
  {
    push(count, T{}); // hack for GCC full specialization in non-namespace scope error
  }

  inline const std::vector<VertexBufferElement>& getElements() const {
    return m_elements;
  };

  inline int getStride() const {
    return m_stride;
  }

private:
  template<typename T>
  void push(unsigned int count, T) = delete;

  void push(unsigned int count, float);
  void push(unsigned int count, unsigned int);

  std::vector<VertexBufferElement> m_elements;
  int m_stride;
};
