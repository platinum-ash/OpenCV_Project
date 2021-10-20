#include <iostream>
#include <string>

#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "image_processing.h"


using namespace cv;
using std::vector;
/****
*	findHSV;
*	Function to help identify HSV color parameters of an image
*	Arguments: takes image with type cv::Mat
*	Returns: No return
****/
void findHSV(Mat img) {
	//Define bounds for HSV space, to be used with trackbars
	int h_min = 0, s_min = 0, v_min = 0;
	int h_max = 179, s_max = 255, v_max = 255;

	//Create window with trackbars to allow changing hue, saturation and value at runtime
	namedWindow("Trackbar", (650, 800));
	createTrackbar("Hue lower", "Trackbar", &h_min, 179);
	createTrackbar("Saturation lower", "Trackbar", &s_min, 255);
	createTrackbar("Value lower", "Trackbar", &v_min, 255);
	createTrackbar("Hue upper", "Trackbar", &h_max, 179);
	createTrackbar("Saturation upper", "Trackbar", &s_max, 255);
	createTrackbar("Value max", "Trackbar", &v_max, 255);

	
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
	return;

}

/****
*	getContours;
*	Function to findand draw detected contours on the original image
*	Arguments: takes Matrix of dilated image and the original image
*	Returns: void, no return
****/
void getContours(Mat img_dil, Mat img)
{
	//Set up according to documentation
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(img_dil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//Define area variable to filter out noise contours by specifying minimum area
	double area = 0;
	//Draw contours one by one while filtering out noise
	for (int i = 0; i < contours.size(); i++)
	{
		area = contourArea(contours[i]);
		//Filter out any object with area <= 2500
		if (area > 2500)
		{
			drawContours(img, contours, i, Scalar(155, 120, 255), 6);
		}
	}

	//Show the result
	imshow("Dilated image passed to the function", img_dil);
	imshow("Contoured image", img);
	waitKey(0);
	return;

}


/****
*	preProcessor;
*	Prepares an image for contour detection.
*	Arguments: Mat type argument of original image
*	Returns: dilated image of type Mat ready for contour detection
****/
Mat preProcessor(Mat img)
{
	Mat img_blur, img_canny, img_dilated, kernel, img_crop, img_mono;
	cvtColor(img, img_mono, COLOR_BGR2GRAY);//Convert color to gray scale
	GaussianBlur(img, img_blur, Size(7, 7), 5, 0);//Add blur
	Canny(img_blur, img_canny, 25, 80);
	kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(img_canny, img_dilated, kernel);
	return img_dilated;
}
