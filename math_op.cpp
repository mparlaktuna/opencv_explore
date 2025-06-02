#include "tools.hpp"

using namespace cv;

// math operations examples
void math_op(cv::Mat image)
{

  double scale = 1/255.0;
  double shift = 0.2;
  Mat image2, image3;
  
  image.convertTo(image2, CV_32FC3, scale, shift);

  image.convertTo(image3, CV_8UC3, 1.0/scale, -shift/scale);
  OpencvHelper::show_multiple_images(ImageDisplay{"first", image},
				     ImageDisplay{"second", image2},
				     ImageDisplay{"third", image3});
  
}

void conversion(cv::Mat image)
{
  Mat image_16 = image.clone();
  Mat image_32 = image.clone();
  // needs the 255 scale since range is between 0-2^16
  image_16.convertTo(image_16, CV_16U, 255);
  image_32.convertTo(image_32, CV_32F, 1/255.0);

  OpencvHelper::show_and_wait(ImageDisplay{"image 16", image_16});
  OpencvHelper::show_and_wait(ImageDisplay{"image 32", image_32});
}

void intensity_scaling(cv::Mat image)
{
  Mat image32 = image.clone();
  Mat image32_scaled, contrast;
  image32.convertTo(image32, CV_32F);

  image32.convertTo(image32_scaled, CV_32F, 1/255.0);
  image32.convertTo(contrast, CV_32F, 1/255.0);
  contrast = contrast * (1 + 50/100.0);
  OpencvHelper::show_multiple_images(ImageDisplay{"scaled", image32_scaled},
				     ImageDisplay{"image 32", image32},
				     ImageDisplay{"contrast", contrast}
				    );
}

void brightness(cv::Mat image)
{
  Mat image32 = image.clone();
  image32.convertTo(image32, CV_32F, 1/255.0);
  Mat bright[3];
  Mat bright_combined;

  split(image32, bright);

  for (int i=0; i < 3; i++)
    {
        add(bright[i], 200/255.0, bright[i]);
   }
  merge(bright, 3, bright_combined);
  double minVal, maxVal;
  minMaxLoc(bright_combined, &minVal, &maxVal);
  bright_combined /= maxVal;
  OpencvHelper::show_multiple_images(ImageDisplay{"image 32", image32},
				     ImageDisplay{"combined", bright_combined}
				    );
}

int main(void) {
  // Read image in GrayScale mode
  Mat image = imread("../boy.jpg");

  math_op(image);
  conversion(image);
  intensity_scaling(image);
  brightness(image);
  return 0;
}
