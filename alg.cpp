#include "alg.h"
#include <opencv2/imgproc.hpp>
#include<iostream>


void grayscaleRed(cv::Mat& image) {

	int H = image.rows;
	int W = image.cols;

	for (int i = 0; i < H; i++) {

		for (int j = 0; j < W; j++) {

			image.at<cv::Vec3b>(i, j)[0] = image.at<cv::Vec3b>(i, j)[2];
			image.at<cv::Vec3b>(i, j)[1] = image.at<cv::Vec3b>(i, j)[2];
		}
	}


}


void grayscaleWeighted(cv::Mat& image) {


	int H = image.rows;
	int W = image.cols;

	for (int i = 0; i < H; i++) {

		for (int j = 0; j < W; j++) {

			int mean = image.at<cv::Vec3b>(i, j)[0] * 0.114 + image.at<cv::Vec3b>(i, j)[1] * 0.587 + image.at<cv::Vec3b>(i, j)[2] * 0.299;
			image.at<cv::Vec3b>(i, j)[0] = mean;
			image.at<cv::Vec3b>(i, j)[1] = mean;
			image.at<cv::Vec3b>(i, j)[2] = mean;
	

		}
	}
}

void darker_lighter(cv::Mat& image, int value) {  


	int H = image.rows;
	int W = image.cols;


	if(value < -100 || value > 100) {
		std::cout << "niepoprawna wartosc\n";
		return;
	}



	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			for (int k = 0; k < 3; k++) {
				int check = image.at<cv::Vec3b>(i, j)[k] * (1.0 - value / 100.0);

				if (check > 255) {
					check = 255;
				}
				if (check < 0) {
					check = 0;
				}


				image.at<cv::Vec3b>(i, j)[k] = check;

			}

		}
	}


}

void binarization(cv::Mat& image, int value) {


	int H = image.rows;
	int W = image.cols;


	grayscaleWeighted(image);


	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
	
		
			if(image.at<cv::Vec3b>(i, j)[0] >= (value/100.0)*255) {
				image.at<cv::Vec3b>(i, j)[0] = 255;
				image.at<cv::Vec3b>(i, j)[1] = 255;
				image.at<cv::Vec3b>(i, j)[2] = 255;
			}
			else {
				image.at<cv::Vec3b>(i, j)[0] = 0;
				image.at<cv::Vec3b>(i, j)[1] = 0;
				image.at<cv::Vec3b>(i, j)[2] = 0;
			}
		
		
		
		}
	}



}



void dylate(cv::Mat& image, int value) {


	cv::Mat ORG = image.clone();
	int H = image.rows;
	int W = image.cols;
	bool flag = false;


	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {

			if (ORG.at<cv::Vec3b>(i, j)[0] != 255) {

				for (int k = i - value; k <= i + value; k++) {
					for (int l = j - value; l <= j + value; l++) {

						if (k < 0 || k >= H || l < 0 || l >= W) { /// otoczenie poza granica obrazka
							continue;
						}

						if (ORG.at<cv::Vec3b>(k, l)[0] == 255) {
							image.at<cv::Vec3b>(i, j)[0] = 255;
							image.at<cv::Vec3b>(i, j)[1] = 255;
							image.at<cv::Vec3b>(i, j)[2] = 255;

							flag = true;
							break;

						}

					}

					if (flag == true) {
						flag = false;
						break;

					}
				}
			}
		}

	}
}


void erode(cv::Mat& image, int value)
{
	cv::Mat ORG = image.clone();
	int H = image.rows;
	int W = image.cols;
	bool flag = false;

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {

			if (ORG.at<cv::Vec3b>(i, j)[0] != 0) {

				for (int k = i - value; k <= i + value; k++) {
					for (int l = j - value; l <= j + value; l++) {

						if (k < 0 || k >= H || l < 0 || l >= W) {
							continue;
						}

						if (ORG.at<cv::Vec3b>(k, l)[0] != 255) {
							image.at<cv::Vec3b>(i, j)[0] = 0;
							image.at<cv::Vec3b>(i, j)[1] = 0;
							image.at<cv::Vec3b>(i, j)[2] = 0;

							flag = true;
							break;
						}
					}

					if (flag == true) {
						flag = false;
						break;
					}
				}
			}
		}
	}
}




void opening(cv::Mat& image, int value)
{
	erode(image, value);
	dylate(image, value);
}


void closing(cv::Mat& image, int value)
{
	dylate(image, value);
	erode(image, value);
}


void convolution( cv::Mat& image, std::vector<double>& filter, int value) {


	cv::Mat ORG = image.clone();
	int H = image.rows;
	int W = image.cols;

	int size = sqrt(filter.size()); // 


	if (size * size != filter.size() || size != 2 * value + 1) {
		std::cout<<"Nieprawidlowy rozmiar filtru";
		return;
	}


	double sum = 0;
	int skip = 0;
	std::vector<int> skipped;
	int count = 0;


	


	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			for (int m = 0; m < 3; m++) {
				for (int k = i - value; k <= i + value; k++) {
					for (int l = j - value; l <= j + value; l++) {
						if (k < 0 || k >= H || l < 0 || l >= W) {
							skip++;
							skipped.push_back((k - i + value)* size + (l - j + value));
							continue;

						}


						sum += ORG.at<cv::Vec3b>(k, l)[m] * filter[(k - i + value) * size + (l - j + value)];


						if (skip != 0) {

							sum += ORG.at<cv::Vec3b>(k, l)[m] * filter[skipped[count]];
							skip--;
							count++;
					
						}

	
					}
				}



				

				if (sum > 255) {
					sum = 255;
				}
				
				if (sum < 0) {
					sum = 0;
				}



				image.at<cv::Vec3b>(i, j)[m] = sum;

				skip = 0;
				sum = 0;
				count = 0;
				skipped.clear();
				
			}
		}
	}


	

}