#include <iostream>

// OpenCV
#include <opencv2/opencv.hpp>

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const std::string vertexShader =
  "#version 330 core\n"
  "\n"
  "layout(location = 0) in vec4 position;\n" // because gl_Position is vec4
  "\n"
  "void main()\n"
  "{\n"
  "   gl_Position = position;\n"
  "}\n";

const std::string fragmentShader =
  "#version 330 core\n"
  "\n"
  "layout(location = 0) out vec4 color;\n"
  "\n"
  "void main()\n"
  "{\n"
  "   color = vec4(0.5, 0.5, 0.5, 1.0);\n"
  "}\n";


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

  unsigned int shader = createShader(vertexShader, fragmentShader);
  glUseProgram(shader);

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
