#include "Renderer.h"

#include <cassert>

#include "GL/glew.h"

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib,
                    const Shader& shader) const
{
  // Bind all
  shader.bind();
  va.bind();
  ib.bind();

  glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::clear() const
{
  glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::setClearColor(const std::vector<float>& colorRgba) const
{
  assert(colorRgba.size() == 4);

  glClearColor(colorRgba[0], colorRgba[1], colorRgba[2], colorRgba[3]);
}
