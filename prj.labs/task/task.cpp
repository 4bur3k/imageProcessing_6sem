#include <opencv2/opencv.hpp>

int main() {
	cv::Mat SingleChanelImame(300, 450, CV_32FC1);
	for (int i = 0; i < 150; i++) {
		for (int j = 0; j < 150; j++) {
			SingleChanelImame.at<float>(i, j) = 0;
		}
	}
	
	for (int i = 150; i < 300; i++) {
		for (int j = 300; j < 450; j++) {
			SingleChanelImame.at<float>(i, j) = 0;
		}
	}
	
	for (int i = 0; i < 150; i++) {
		for (int j = 150; j < 300; j++) {
			SingleChanelImame.at<float>(i, j) = 127 / 255.0;
			SingleChanelImame.at<float>(j, i) = 127 / 255.0;
		}
	}
	
	for (int i = 150; i < 300; i++) {
		for (int j = 150; j < 300; j++) {
			SingleChanelImame.at<float>(i, j) = 255 / 255.0;
			SingleChanelImame.at<float>(i - 150, j + 150) = 255 / 255.0;
		}
	}

	//G
	cv::circle(SingleChanelImame, cv::Point(225, 75), 70, 180 / 255.0, -1);
	cv::circle(SingleChanelImame, cv::Point(75, 225), 70, 100 / 255.0, -1);

	//B
	cv::circle(SingleChanelImame, cv::Point(75, 75), 70, 255 / 255.0, -1);
	cv::circle(SingleChanelImame, cv::Point(375, 225), 70, 200 / 255.0, -1);

	//W
	cv::circle(SingleChanelImame, cv::Point(225, 225), 70, 50 / 255.0, -1);
	cv::circle(SingleChanelImame, cv::Point(375, 75), 70, 0, -1);

	
	cv::Mat Img_1(2, 2, CV_32S);
	Img_1 = 0;
	Img_1.at<int>(0, 0) = 1;
	Img_1.at<int>(1, 1) = -1;

	cv::Mat Img_2(2, 2, CV_32S);
	Img_2 = 0;
	Img_2.at<int>(0, 1) = 1;
	Img_2.at<int>(1, 0) = -1;

	
	cv::Mat Img_1_filtered = SingleChanelImame.clone();
	Img_1_filtered = 0;
	cv::filter2D(SingleChanelImame, Img_1_filtered, -1, Img_1, cv::Point(0, 0));

	cv::Mat Img_2_filtered = SingleChanelImame.clone();
	Img_2_filtered = 0;
	cv::filter2D(SingleChanelImame, Img_2_filtered, -1, Img_2, cv::Point(0, 0));

	
	cv::Mat Intermed(SingleChanelImame.size(), CV_32FC1);
	for (int i = 0; i < Img_1_filtered.rows; i++) {
		for (int j = 0; j < Img_1_filtered.cols; j++) {
			Intermed.at<float>(i, j) = std::sqrt(Img_1_filtered.at<float>(i, j) * Img_1_filtered.at<float>(i, j) + Img_2_filtered.at<float>(i, j) * Img_2_filtered.at<float>(i, j));
		}
	}

	Img_1_filtered = (Img_1_filtered + 1) / 2;
	Img_2_filtered = (Img_2_filtered + 1) / 2;


	cv::imwrite("Img_original.png", SingleChanelImame * 255);
	cv::imwrite("Img_1.png", Img_1_filtered * 255);
	cv::imwrite("Img_2.png", Img_2_filtered * 255);
	cv::imwrite("Img_intermediate.png", Intermed * 255);


	return 0;
}
