#include <opencv2/opencv.hpp>
#include <fmt/core.h>

using namespace cv;
using namespace std;
using namespace fmt;

struct ImageDisplay
{
  const string name;
  Mat image;
};

struct OpencvHelper
{

  // Args are classes derived from ImageDisplay
  template <typename A, typename... Args>
  static void show_multiple_images(A&& a, Args&& ...args)
  {
    int width=0;
    int height=0;
    auto f = [&](const ImageDisplay& imd)
    {
      width += imd.image.cols;
      height = max(height, imd.image.rows);
    };
    f(a);
    (f(args), ...);
    print("Width: {}, height: {}\n", width, height);
    cv::Mat combined(height, width, a.image.type());

    int col = 0;
    auto f2 = [&](const ImageDisplay& imd)
    {
      print("show: {}\n", imd.name);
      imd.image.copyTo(combined(cv::Rect(col, 0, imd.image.cols, imd.image.rows)));
      col += imd.image.cols;
    };
    f2(a);
    (f2(args), ...);

    cv::imshow("Combined Image", combined);
    cv::waitKey(0);
    cv::destroyAllWindows();
  }

    // Args are classes derived from ImageDisplay
  static void show_and_wait(const ImageDisplay& imd)
  {
    cv::imshow(imd.name, imd.image);
    cv::waitKey(0);
    cv::destroyAllWindows();
  }
};
