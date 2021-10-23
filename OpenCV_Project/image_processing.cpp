#include <iostream>
#include <string>

#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "image_processing.h"


using namespace cv;
using std::vector;

//Define some Scalar colors
#define BORDER_PINK	Scalar(155, 120, 255)

/****
*	findHSV;
*	Function to help identify HSV(Hue, Saturation and value) color parameters of an image
*	Arguments: takes image with type cv::Mat
*	Returns: No return
****/
void findHSV(Mat &img) {
	//Define bounds for HSV space, to be used with trackbars
	//We will search image for pixels with range of these HSV values
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

	
	Mat img_new_colors, result;
	//Convert image to HSV color space
	cvtColor(img, img_new_colors, COLOR_BGR2HSV);
	while (true) {

		Scalar lower_b(h_min, s_min, v_min);
		Scalar upper_b(h_max, s_max, v_max);
		imshow("Original", img);
		//Call inRange to find pixels with HSV color within given range
		inRange(img_new_colors, lower_b, upper_b, result);
		imshow("Image", result);
		waitKey(1);

	}
	return;

}

/****
*	preProcessor;
*	Prepares an image for contour detection.
*	Arguments: Mat type argument of original image
*	Returns: dilated image of type Mat ready for contour detection
****/

Mat preProcessor(Mat &img)
{
	Mat img_blur, img_canny, img_dilated, kernel, img_crop, img_mono;
	cvtColor(img, img_mono, COLOR_BGR2GRAY);//Convert color to gray scale
	GaussianBlur(img, img_blur, Size(3, 3), 5, 0);//Add blur
	Canny(img_blur, img_canny, 50, 150);
	kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(img_canny, img_dilated, kernel);
	return img_dilated;
}

/****
*	findContours
*	Function finds all contours with a area based noise filter
*	Arguments : original image of type Mat and the preprocessed image for finding contours
*	Returns: vector of Point vectors
****/

vector<vector<Point>> findContoursLocal(Mat &img_dil) {
	//Set up according to documentation
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(img_dil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	vector<vector<Point>> contours_filtered;

	//Define area variable to filter out noise contours by specifying minimum area
	double area = 0;
	//Draw contours one by one while filtering out noise
	for (int i = 0; i < contours.size(); i++)
	{
		area = contourArea(contours[i]);
		//Filter out any object with area <= 2500
		if (area > 2500)
		{
			contours_filtered.push_back(contours[i]);
		}
	}

	return contours_filtered;
}

/****
*	drawContours
*	Function to draw detected contours on the original image
*	Arguments: takes Matrix of image and the contours
*	Returns: void, no return
****/

void drawContoursLocal(Mat &img, vector<vector<Point>> &contours)
{
	
	for (int i = 0; i < contours.size(); i++)
	{
		drawContours(img, contours, i, BORDER_PINK, 6);	
	}

	//Show the result
	imshow("Contoured image", img);
	waitKey(0);
	return;

}

/****
*	shapeDetect;
*	Function to detect and display very basic and obvious shapes : Triangle, Rectangular, Circle
*	Arguments: takes Matrix of dilated image and the original image
*	Returns: void, no return
****/

void shapeDetect(Mat &img, Mat &img_dil) {
	//Get all contours
	vector<vector<Point>> contours = findContoursLocal(img_dil);

	float perimeter;
	std::string shape;
	int num_edges;
	int contour_size = contours.size();//get and store contour size
	vector<vector<Point>> conPoly(contour_size);//create vector to store approxPolyDP results
	vector<Rect> labelBound(contours.size());//Create vector to hold points for drawing boundary around shape

	for (int i = 0; i < contour_size; i++)
	{
		//Use 20% perimeter as the approximate allowable distance b/w original curve and new points
		perimeter = arcLength(contours[i], true);
		approxPolyDP(contours[i], conPoly[i], 0.02f * perimeter, true);

		//Get the bounding rectangle from the detected edges for drawing label boundary
		labelBound[i] = boundingRect(conPoly[i]);

		//Give shapes names according the number of detected edges
		num_edges = conPoly[i].size();
		if (num_edges == 3) shape = "Triangle";
		if (num_edges == 4) shape = "Rectangular";
		if (num_edges > 4)  shape = "Circle";

		//Draw name of shapes along with highlighting boundary around the shape
		rectangle(img, labelBound[i], Scalar(255, 0, 255));
		putText(img, shape, { labelBound[i].x, labelBound[i].y - 8 }, FONT_HERSHEY_COMPLEX, 0.60f, 4);
		drawContours(img, conPoly, i, Scalar(0, 0, 0), 1);
	}
	imshow("Shapes", img);
	waitKey(0);
}

/****
*	findLargestRect;
*	Function to find the edge coordinates of the largest rectangle in an image for doc scanning
*	Arguments: takes Matrix of dilated image( preprocessed )
*	Returns: vector of point containing 4 edge coordinates
****/

vector<Point> findLargestRect(Mat &img_dil) {
	//Get all contours
	vector<vector<Point>> contours = findContoursLocal(img_dil);

	float perimeter;
	int area, biggest = 0;
	int contour_size = contours.size();//get and store contour size
	vector<vector<Point>> conPoly(contour_size);//create vector to store approxPolyDP results
	vector<Point> largestRect;

	for (int i = 0; i < contour_size; i++) 
	{

		// Use 20 % perimeter as the approximate allowable distance b / w original curve and new points
		perimeter = arcLength(contours[i], true);
		area = contourArea(contours[i]);
		approxPolyDP(contours[i], conPoly[i], 0.02f * perimeter, true);
		//Find the largest rectangle
		if(area > biggest && conPoly[i].size() == 4)
		{
			//Store the coordinates of the largest rectangle by area found so far
			largestRect = {conPoly[i][0], conPoly[i][1] , conPoly[i][2] , conPoly[i][3]};
			biggest = area;
		}
	}

	return largestRect;
}


Mat changePerspective(Mat &img, vector<Point> &coordinates) {
	float width, height;
	width = 700.0f;
	height = 750.0f;

	Mat transformed, img_out;

	//Set up for getting transformation matrix as per docs
	Point2f transform_src[4] = { coordinates[1],coordinates[0], coordinates[2], coordinates[3] };
	Point2f transform_dst[4] = { {0.0f, 0.0f}, {width, 0.0f}, {0.0f, height}, {width, height} };
	//Using warpPerspective to change perspective with transformation matrix from getPerspectiveTransform
	transformed = getPerspectiveTransform(transform_src, transform_dst);
	warpPerspective(img, img_out, transformed, Point(width, height));
	
	return img_out;

}

void scanDocument(Mat &img, Mat &img_dil) {

	vector<Point> detectedEdges = findLargestRect(img_dil);
	/*for (int i = 0; i < detectedEdges.size(); i++)
	{
		circle(img, detectedEdges[i], 6, BORDER_PINK, FILLED);
	}*/
	
	imshow("Detected edges", changePerspective(img, detectedEdges));
	waitKey(20000);

}