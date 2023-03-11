#include "Window.h"

#include <iostream>
#include <system_error>

GlfwWindow::GlfwWindow(int width, int height, const std::string& name)
  : m_window{}
{
  if (!glfwInit())
    throw std::system_error({}, "Failed to initialize GLFW");

  m_window = glfwCreateWindow(width, height, name.c_str(), {}, {});

  if (!m_window) {
    glfwTerminate();

    throw std::system_error({}, "Failed to open GLFW window");
  }

  glfwMakeContextCurrent(m_window);
}

GlfwWindow::~GlfwWindow()
{
  if (m_window) {
    glfwDestroyWindow(m_window);
    glfwTerminate();
  }
}

bool GlfwWindow::isShouldBeClosed() const
{
  return glfwWindowShouldClose(m_window);
}

void GlfwWindow::swapBuffer()
{
  glfwSwapBuffers(m_window);
}

void GlfwWindow::pollEvents()
{
  glfwPollEvents();
}
