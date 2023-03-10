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
#include "Texture.h"

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

  std::shared_ptr<Window> window =
      std::make_shared<GlfwWindow>(width, height, "TestOpenGL");

  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;

    return -1;
  }

  const std::vector<float> positions{
    // Background
    -1.0f, -1.0f, 0.0f, 0.0f,
     1.0f,  1.0f, 1.0f, 1.0f,
     1.0f, -1.0f, 1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f, 1.0f,

    // Front
    -0.5f, -0.5f, 0.0f, 0.0f,
     0.5f,  0.5f, 1.0f, 1.0f,
     0.5f, -0.5f, 1.0f, 0.0f,
    -0.5f,  0.5f, 0.0f, 1.0f
  };

  unsigned int offset = 0; // Num of vertices

  const std::vector<unsigned int> indiciesBackground{
    offset + 0, offset + 1, offset + 2,
    offset + 0, offset + 1, offset + 3
  };

  offset += 4;

  const std::vector<unsigned int> indiciesFront{
    offset + 0, offset + 1, offset + 2,
    offset + 0, offset + 1, offset + 3
  };

  // Vertex Array
  VertexArray va;

  // Vertex buffer
  VertexBuffer vb(positions.data(), sizeof(float) * positions.size());

  VertexBufferLayout layout;
  layout.push<float>(2); // Vertex positions
  layout.push<float>(2); // Texture positions

  va.addBuffer(vb, layout);

  // Index (element) buffer
  IndexBuffer ibBackground(indiciesBackground.data(), indiciesBackground.size());
  IndexBuffer ibFront(indiciesFront.data(), indiciesFront.size());

  // Shaders
  Shader shader("res/shaders/vertex.shader", "res/shaders/fragment.shader");
  shader.bind();

  Renderer renderer;

  Texture textureFront("res/textures/pikachu.png");
  textureFront.bind(0);
  shader.setUniform1i("u_Texture", 0);

  // Unbind all
  va.unbind();
  shader.unbind();
  vb.unbind();
  ibBackground.unbind();
  ibFront.unbind();
  textureFront.unbind();

  while (!window->isShouldBeClosed()) {
    cap >> img;

    if (img.empty())
      continue;

    cv::imshow(windowName, img);
    cv::waitKey(25);

    renderer.setClearColor({0.3, 0.8, 0.3, 1.0});
    renderer.clear();

    Texture textureBackground(img);
    textureBackground.bind(0);
    renderer.draw(va, ibBackground, shader);

    textureFront.bind(0);
    renderer.draw(va, ibFront, shader);

    window->swapBuffer();
    window->pollEvents();
  }

  cap.release();

  return 0;
}
