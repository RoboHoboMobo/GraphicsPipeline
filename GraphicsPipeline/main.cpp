#include <iostream>

// OpenCV
#include <opencv2/opencv.hpp>

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{

}

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

  // Triangle section
  float positions[] = {
    -0.5f, -0.5f,
     0.0f,  0.5f,
     0.5f, -0.5f
  };

  unsigned int buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  while (!glfwWindowShouldClose(window)) {
    cap >> img;

    if (img.empty())
      continue;

    cv::imshow(windowName, img);
    cv::waitKey(25);

    glClearColor(0.2, 0.7, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  cap.release();
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
