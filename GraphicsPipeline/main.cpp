#include <iostream>

// OpenCV
#include <opencv2/opencv.hpp>

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"

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

  GLFWwindow* window;

  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;

    return -1;
  }

  window = glfwCreateWindow(width, height, "TestOpenGL", {}, {});

  if (!window) {
    std::cerr << "Failed to open GLFW window" << std::endl;

    glfwTerminate();

    return -1;
  }

  glfwMakeContextCurrent(window);

  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;

    return -1;
  }

  { // scope in order to call ~VertexBuffer() before context destruction
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

    while (!glfwWindowShouldClose(window)) {
      cap >> img;

      if (img.empty())
        continue;

      cv::imshow(windowName, img);
      cv::waitKey(25);

      renderer.setClearColor({0.3, 0.8, 0.3, 1.0});
      renderer.clear();

      renderer.draw(va, ib, shader);

      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  }

  cap.release();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
