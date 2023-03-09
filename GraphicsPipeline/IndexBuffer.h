#pragma once

class IndexBuffer {
public:
  IndexBuffer(const unsigned int* data, unsigned int num);
  ~IndexBuffer();

  void bind() const;
  void unbind() const;

  inline unsigned int getCount() const { return m_count; };

private:
  unsigned int m_rendererId;
  unsigned int m_count;
};
