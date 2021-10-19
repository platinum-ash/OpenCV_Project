#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <string>



using namespace std;
using namespace cv;


void getContours(Mat img_dil, Mat img){
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(img_dil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE),
	drawContours(img, contours, -1, Scalar(255, 0, 255), 2);
	imshow("Contoured image", img);
	waitKey(0);

}



Mat preProcessor(Mat img) {
	Mat img_blur, img_canny, img_dilated, kernel, img_crop, img_mono;

	//Test basic functions
	cvtColor(img, img_mono, COLOR_BGR2GRAY);
	GaussianBlur(img, img_blur, Size(7, 7), 5, 0);
	Canny(img_blur, img_canny, 25, 80);
	kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(img_canny, img_dilated, kernel);
	return img_dilated;
}



int main() {
	Mat img;
	string path = "Images//img6.png";
	img = imread(path);
	Mat img_contour = preProcessor(img);
	getContours(img_contour, img);

	/*
	imshow("From the function", img_contour);
	waitKey(0);*/
	return EXIT_SUCCESS;
}