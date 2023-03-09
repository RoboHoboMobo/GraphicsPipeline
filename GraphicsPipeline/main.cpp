#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// OpenCV
#include <opencv2/opencv.hpp>

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Helpers
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"

std::string parseShader(const std::string& filepath)
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

static unsigned int compileShader(unsigned int shaderType, const std::string& source)
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

static unsigned int createShader(const std::string& vertexShader,
                                 const std::string& fragmentShader)
{
  unsigned int prog = glCreateProgram();
  unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

  glAttachShader(prog, vs);
  glAttachShader(prog, fs);

  glLinkProgram(prog);
  glValidateProgram(prog);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return prog;
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

    const std::string vertexShader = parseShader("res/shaders/shader.vertex");
    const std::string fragmentShader = parseShader("res/shaders/shader.fragment");
    unsigned int shader = createShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    // Unbind all
    va.unbind();
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(window)) {
      cap >> img;

      if (img.empty())
        continue;

      cv::imshow(windowName, img);
      cv::waitKey(25);

      glClearColor(0.2, 0.7, 0.2, 1.0);
      glClear(GL_COLOR_BUFFER_BIT);

      // Bind all
      glUseProgram(shader);
      va.bind();
      ib.bind();

      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

      glfwSwapBuffers(window);
      glfwPollEvents();
    }

    glDeleteProgram(shader);

  }

  cap.release();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
