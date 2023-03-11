#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>

Shader::Shader(const std::string& vertexShaderPath,
               const std::string& fragmentShaderPath)
  : m_rendererId{}
  , m_vertexShaderFilepath{vertexShaderPath}
  , m_fragmentShaderFilepath{fragmentShaderPath}
  , m_cache{}
{
  unsigned int prog = glCreateProgram();
  unsigned int vs = compileShader(GL_VERTEX_SHADER, parseShader(vertexShaderPath));
  unsigned int fs = compileShader(GL_FRAGMENT_SHADER, parseShader(fragmentShaderPath));

  glAttachShader(prog, vs);
  glAttachShader(prog, fs);

  glLinkProgram(prog);
  glValidateProgram(prog);

  glDeleteShader(vs);
  glDeleteShader(fs);

  m_rendererId = prog;
}

Shader::~Shader()
{
  glDeleteProgram(m_rendererId);
}

void Shader::bind() const
{
  glUseProgram(m_rendererId);
}

void Shader::unbind() const
{
  glUseProgram(0);
}

void Shader::setUniform1i(const std::string& name, int value)
{
  glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform4f(const std::string& name, const std::vector<float>& v)
{
  glUniform4f(getUniformLocation(name), v[0], v[1], v[2], v[3]);
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
  glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::getUniformLocation(const std::string& name)
{
  if (m_cache.find(name) != m_cache.cend())
    return m_cache.at(name);

  unsigned int location = glGetUniformLocation(m_rendererId, name.c_str());
  m_cache.insert(std::make_pair(name, location));

  if (location == -1)
    std::cout << "Warning: uniform '" << name << "' doen't exist" << std::endl;

  return location;
}

std::string Shader::parseShader(const std::string& filepath)
{
  std::fstream file(filepath);
  std::string str;
  std::stringstream ss;

  bool isOk{};
  while (getline(file, str)) {
    if (str.find("#version") != std::string::npos)
      isOk = true;

    ss << str << '\n';
  }

  if (!isOk)
    std::cerr << "Failed to parse " << filepath << "shader"<< std::endl;

  return isOk ? ss.str() : std::string();
}

unsigned int Shader::compileShader(unsigned int shaderType, const std::string& source)
{
  unsigned int id = glCreateShader(shaderType);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int result{};
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);

  if (!result) {
    int len{};
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
    char* message = static_cast<char*>(alloca(len * sizeof(char)));
    glGetShaderInfoLog(id, len, &len, message);

    std::string typeString = shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment";

    std::cerr << "Failed to compile " << typeString << "shader"<< std::endl;
    std::cerr << message << std::endl;

    glDeleteShader(id);

    return 0;
  }

  return id;
}
