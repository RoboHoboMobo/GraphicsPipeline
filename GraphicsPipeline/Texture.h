#pragma once

#include <string>
#include <memory>

#include <opencv2/opencv.hpp>

class Texture {
public:
  Texture(const std::string& path);
  Texture(const cv::Mat& img);
  ~Texture();

  void bind(unsigned int slot = 0) const;
  void unbind() const;

  inline int getWidht() const { return m_width; }
  inline int getHeight() const { return m_height; }

private:
  unsigned int m_rendererId;
  std::string m_filePath;
  std::shared_ptr<unsigned char> m_localBuffer;
  int m_width;
  int m_height;
  int m_bpp;
};
