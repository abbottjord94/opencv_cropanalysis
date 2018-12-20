#include "opencv2\opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {

	float rval=0, nval=0, ndvi=0, gval = 0, ndwi=0, min=0;

	cout << "Image Reader 9000\n";
	Mat orig = imread("tst2.jpg", CV_LOAD_IMAGE_UNCHANGED);
	// Mat nir = imread("nir.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat splitChannels[3];
	Mat ndviImage(2464, 3280, CV_8UC3, cv::Scalar(0, 0, 0));
	// Mat ndwiImage(2464, 3280, CV_8UC3, cv::Scalar(0, 0, 0));

	//0 - NIR
	//1 - Red

	split(orig, splitChannels);

	nval = splitChannels[0].at<uint8_t>(0, 0);
	rval = splitChannels[1].at<uint8_t>(0, 0);
	min = ((nval - rval) / (nval + rval));
	for (int r = 0; r < splitChannels[0].rows; r++) {
		for (int c = 0; c < splitChannels[0].cols; c++) {
			nval = splitChannels[0] .at<uint8_t>(r, c);
			rval = splitChannels[1].at<uint8_t>(r, c);
			ndvi = (1.5*(nval - rval)) / (nval + rval + 0.5);
			if (ndvi < min) { min = ndvi; }

		}
	}
	for (int r = 0; r < splitChannels[0].rows; r++) {
		for (int c = 0; c < splitChannels[0].cols; c++) {
			nval = splitChannels[0].at<uint8_t>(r, c);
			rval = splitChannels[1].at<uint8_t>(r, c);
			ndvi = (1.5*(nval - rval)) / (nval + rval + 0.5);
			ndviImage.at<Vec3b>(r, c)[0] = (255 * ((ndvi - min)) + 1.5);
			ndviImage.at<Vec3b>(r, c)[1] = 255;
			ndviImage.at<Vec3b>(r, c)[2] = 255;

		}
	}
	/*
	for (int r = 0; r < splitChannels[0].rows; r++) {
		for (int c = 0; c < splitChannels[0].cols; c++) {
			nval = splitChannels[0].at<uint8_t>(r, c);
			gval = splitChannels[2].at<uint8_t>(r, c);
			ndwi = ((gval - nval) / (gval + nval));
			ndwiImage.at<Vec3b>(r, c)[0] = (200 * (ndwi+1));
			ndwiImage.at<Vec3b>(r, c)[1] = 255;
			ndwiImage.at<Vec3b>(r, c)[2] = 255;

		}
	}
	*/
	cvtColor(ndviImage, ndviImage, CV_HSV2RGB);
	// cvtColor(ndwiImage, ndwiImage, CV_HSV2RGB);
	imshow("ndvi", ndviImage);
	// imshow("ndwi", ndwiImage);
	imwrite("ndvi5.jpg", ndviImage);
	// imwrite("ndwi4.jpg", ndwiImage);
	waitKey();
	return 0;

}
