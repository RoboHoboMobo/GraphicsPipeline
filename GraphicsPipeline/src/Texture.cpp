#include "Texture.h"

#include "GL/glew.h"

#include "stb_image/stb_image.h"

Texture::Texture(const std::string& path)
  : m_rendererId{}
  , m_filePath{path}
  , m_localBuffer{}
  , m_width{}
  , m_height{}
  , m_bpp{}
{
  stbi_set_flip_vertically_on_load(1);

  auto deleter = [](unsigned char* buffer) {
    stbi_image_free(buffer);
  };

  m_localBuffer = std::shared_ptr<unsigned char>(
                stbi_load(m_filePath.c_str(), &m_width, &m_height, &m_bpp, 4), deleter);

  glGenTextures(1, &m_rendererId);
  glBindTexture(GL_TEXTURE_2D, m_rendererId);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

  glTexImage2D(GL_TEXTURE_2D,     // Type of texture
               0,                 // Pyramid level (for mip-mapping) - 0 is the top level
               GL_RGBA,           // Internal colour format to convert to
               m_width,           // Image width  i.e. 640 for Kinect in standard mode
               m_height,          // Image height i.e. 480 for Kinect in standard mode
               0,                 // Border width in pixels (can either be 1 or 0)
               GL_RGBA,           // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
               GL_UNSIGNED_BYTE,  // Image data type
               m_localBuffer.get());    // The actual image data itself

  glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const cv::Mat& img)
{
  unsigned int textureId;

  glGenTextures(1, &m_rendererId);
  glBindTexture(GL_TEXTURE_2D, m_rendererId);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

  cv::Mat image = img.clone();

  if (!image.empty()) {
    cv::flip(image, image, 0);

    auto deleter = [](unsigned char array[]) {
      delete[] array;
    };

    const size_t size = image.total() * image.elemSize();
    m_localBuffer = std::shared_ptr<unsigned char>(new unsigned char[size], deleter);

    std::copy(image.data, image.data + size, m_localBuffer.get());
  }

  glTexImage2D(GL_TEXTURE_2D,         // Type of texture
               0,                     // Pyramid level (for mip-mapping) - 0 is the top level
               GL_RGB,                // Internal colour format to convert to
               image.cols,            // Image width  i.e. 640 for Kinect in standard mode
               image.rows,            // Image height i.e. 480 for Kinect in standard mode
               0,                     // Border width in pixels (can either be 1 or 0)
               GL_BGR,                // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
               GL_UNSIGNED_BYTE,      // Image data type
               m_localBuffer.get());  // The actual image data itself

  glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
  glDeleteTextures(1, &m_rendererId);
}

void Texture::bind(unsigned int slot) const
{
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, m_rendererId);
}

void Texture::unbind() const
{
  glBindTexture(GL_TEXTURE_2D, 0);
}
