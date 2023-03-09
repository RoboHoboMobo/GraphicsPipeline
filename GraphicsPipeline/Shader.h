#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class Shader
{
public:
  Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
  ~Shader();

  void bind() const;
  void unbind() const;

  void setUniform4f(const std::string& name, const std::vector<float>& v);

private:
  int getUniformLocation(const std::string& name);
  std::string parseShader(const std::string& filepath);
  unsigned int compileShader(unsigned int shaderType, const std::string& source);

  unsigned int m_rendererId;
  std::string m_vertexShaderFilepath;
  std::string m_fragmentShaderFilepath;
  std::unordered_map<std::string, int> m_cache;
};
