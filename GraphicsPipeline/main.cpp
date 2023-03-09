#include <iostream>
#include <memory>

// OpenCV
#include <opencv2/opencv.hpp>

// OpenGL
#include <GL/glew.h>

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Window.h"

int main()
{
  constexpr int height = 480;
  constexpr int width = 640;

  cv::Mat img;
  const std::string windowName{"TestOpenCV"};
  cv::namedWindow(windowName);

  cv::VideoCapture cap(0);

  if (!cap.isOpened()) {
    std::cerr << "Failed to open camera" << std::endl;

    return -1;
  }

  std::shared_ptr<Window> window = std::make_shared<GlfwWindow>(width, height, "TestOpenGL");

  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;

    return -1;
  }

  const std::vector<float> positions{
    -0.5f, -0.5f,
     0.5f,  0.5f,
     0.5f, -0.5f,
    -0.5f,  0.5f
  };

  const std::vector<unsigned int> indicies{
    0, 1, 2,
    0, 1, 3
  };

  // Vertex Array
  VertexArray va;

  // Vertex buffer
  VertexBuffer vb(positions.data(), sizeof(float) * positions.size());

  VertexBufferLayout layout;
  layout.push<float>(2);

  va.addBuffer(vb, layout);

  // Index (element) buffer
  IndexBuffer ib(indicies.data(), indicies.size());

  // Shaders
  Shader shader("res/shaders/shader.vertex", "res/shaders/shader.fragment");
  shader.bind();

  Renderer renderer;

  // Unbind all
  va.unbind();
  shader.unbind();
  vb.unbind();
  ib.unbind();

  while (!window->isShouldBeClosed()) {
    cap >> img;

    if (img.empty())
      continue;

    cv::imshow(windowName, img);
    cv::waitKey(25);

    renderer.setClearColor({0.3, 0.8, 0.3, 1.0});
    renderer.clear();

    renderer.draw(va, ib, shader);

    window->swapBuffer();
    window->pollEvents();
  }

  cap.release();

  return 0;
}
