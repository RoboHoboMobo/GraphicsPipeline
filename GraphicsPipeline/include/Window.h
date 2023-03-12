#pragma once

#include <string>

#include <GLFW/glfw3.h>

class Window
{
public:
  virtual bool isShouldBeClosed() const = 0;
  virtual void swapBuffer() = 0;
  virtual void pollEvents() = 0;
};

class GlfwWindow : public Window
{
public:
  GlfwWindow(int width, int height, const std::string& name);
  virtual ~GlfwWindow();

  bool isShouldBeClosed() const override;
  void swapBuffer() override;
  void pollEvents() override;

private:
  GLFWwindow* m_window;
};

