#include <opencv2/opencv.hpp>

int main() {
  cv::Mat I_1(60, 768, CV_8UC1);
  // draw dummy image
  I_1 = 0;

  cv::TickMeter timer;

  //making single channel picture with gradient
  for (int i = 0; i < I_1.rows; i ++) {
	  for (int j = 0; j < I_1.cols; j++) {
		  I_1.at<uchar>(i, j) = j / 3;
	  }
  }

  cv::Mat G_1 = I_1.clone();

  timer.start();

  G_1.convertTo(G_1, CV_32FC1, 1/255.);

  cv::pow(G_1, 2.2, G_1);

  G_1.convertTo(G_1, CV_8UC1, 255);

  timer.stop();
  std::cout << "G_1 timer = " << timer.getTimeSec() << std::endl;
  timer.reset();

  cv::Mat G_2 = I_1.clone();

  timer.start();

  for (int i = 0; i < G_2.rows; i++)
	  for (int j = 0; j < G_2.cols; j++) {
		  G_2.at<uchar>(i, j) = std::pow(G_2.at<uchar>(i, j) / 255., 2.2) * 255;
	  }

  timer.stop();
  std::cout << "G_2 timer = " << timer.getTimeSec() << std::endl;

  
  // save result
  //cv::imwrite("lab01.png", I_1);
  cv::imshow("I_1", I_1);
  cv::imshow("G_1", G_1);
  cv::imshow("G_2", G_2);

  cv::waitKey(0);
}
