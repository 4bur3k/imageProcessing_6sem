#include <opencv2/opencv.hpp>

//Changing brightness of (Mat) image on (double) ratio;
cv::Mat changeBrightness(cv::Mat img, double ratio) {
	cv::Mat image = img.clone();

	for (int i = 0; i < image.rows; i++)
		for (int j = 0; j < image.cols; j++) {
			image.at<uchar>(i, j) = std::pow(image.at<uchar>(i, j) / 255., ratio) * 255;
		}

	return image;
}

int main() {
	cv::Mat originalImage = cv::imread("../../../data/cross_0256x0256.png");
	cv::imwrite("(lab03_rgb.png", originalImage);
	

	//non-trivial function of brightness transformation
	cv::imshow("orginal image", originalImage);
	
	cv::Mat img = changeBrightness(originalImage, 2.2);

	cv::imshow("singlechanel", originalImage);
	cv::imshow("singlechanelfoo", img);

	cv::waitKey(0);
}