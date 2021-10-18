#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <string>



using namespace std;
using namespace cv;

int main() {

	int h_min = 0, s_min = 0, v_min = 0;
	int h_max = 179, s_max = 255, v_max = 255;

	namedWindow("Trackbar", (650, 800));
	createTrackbar("Hue lower", "Trackbar", &h_min, 179);
	createTrackbar("Saturation lower", "Trackbar", &s_min, 255);
	createTrackbar("Value lower", "Trackbar", &v_min, 255);
	createTrackbar("Hue upper", "Trackbar", &h_max, 179);
	createTrackbar("Saturation lower", "Trackbar", &s_max, 255);
	createTrackbar("Value max", "Trackbar", &v_max, 255);

	Mat img = imread("Images//img5.jpg");
	Mat img_new_colors, mask;
	cvtColor(img, img_new_colors, COLOR_BGR2HSV);
	//imshow("Image", img_new_colors);
	while (true) {

		Scalar lower_b(h_min, s_min, v_min);
		Scalar upper_b(h_max, s_max, v_max);
		
		imshow("Original", img);
		
		inRange(img_new_colors, lower_b, upper_b, mask);
		imshow("Image", mask);
		waitKey(1);

	}

	return 0;
}