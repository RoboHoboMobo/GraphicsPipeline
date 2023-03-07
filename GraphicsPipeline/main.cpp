#include <iostream>

#include <opencv2/opencv.hpp>

int main()
{
  cv::Mat img;

  const std::string windowName{"Test"};
  cv::namedWindow(windowName);

  cv::VideoCapture cap(0);

  if (!cap.isOpened()) {
    std::cerr << "Couldn't open camera" << std::endl;

    return -1;
  }

  while (true) {
    cap >> img;

    if (img.empty())
      continue;

    cv::imshow(windowName, img);

    char c = (char)cv::waitKey(200);

    if(c==27)
      break;
  }

  cap.release();
  cv::destroyAllWindows();

  return 0;
}
