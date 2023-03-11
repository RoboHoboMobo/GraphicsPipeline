#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer{
public:
  Renderer() = default;
  ~Renderer() = default;

  void draw(const VertexArray&, const IndexBuffer&, const Shader&) const;
  void clear() const;
  void setClearColor(const std::vector<float>& colorRgba) const;
};
