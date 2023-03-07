#include <iostream>

// OpenCV
#include <opencv2/opencv.hpp>

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLuint imageToTexture(const cv::Mat& img)
{
  GLuint textureId;

  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);

  if (img.empty())
    return textureId;

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Set texture clamping method
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

  cv::cvtColor(img, img, cv::COLOR_RGB2BGR);

  glTexImage2D(GL_TEXTURE_2D,     // Type of texture
               0,                 // Pyramid level (for mip-mapping) - 0 is the top level
               GL_RGB,            // Internal colour format to convert to
               img.cols,          // Image width  i.e. 640 for Kinect in standard mode
               img.rows,          // Image height i.e. 480 for Kinect in standard mode
               0,                 // Border width in pixels (can either be 1 or 0)
               GL_RGB,            // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
               GL_UNSIGNED_BYTE,  // Image data type
               img.ptr());        // The actual image data itself

  return textureId;
}

void drawImage(int width, int height, const cv::Mat& img)
{
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);     // Operate on model-view matrix

  glEnable(GL_TEXTURE_2D);

  GLuint tex = imageToTexture(img);

  glBegin(GL_QUADS);
  glTexCoord2i(0, 0); glVertex2i(-1, 1);
  glTexCoord2i(0, 1); glVertex2i(-1, -1);
  glTexCoord2i(1, 1); glVertex2i(1, -1);
  glTexCoord2i(1, 0); glVertex2i(1, 1);
  glEnd();

  glDeleteTextures(1, &tex);
  glDisable(GL_TEXTURE_2D);
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

  while (!glfwWindowShouldClose(window)) {
    cap >> img;

    if (img.empty())
      continue;

    cv::imshow(windowName, img);
    cv::waitKey(25);

    drawImage(width, height, img);
    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  cap.release();
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
