#include <iostream>
#include <string>

#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "image_processing.h"


using namespace cv;
using std::cout;
using std::getline;
using std::string;
using std::cin;


/****
*	checkSize;
*	Check size of image and shrink it if necessary
*	Arguments: Image of type Mat passed by reference
*	Returns: void
*****/
//
inline void checkSize(Mat &img) 
{
	Size img_size = img.size();
	int width = img_size.width;
	int height = img_size.height;
	if (height > 1000 || width > 1000) 
	{
		resize(img, img, Size(800, 600));
	}
}

int main() 
{
	Mat img;
	//For now use console input for the image file path.
	//TODO : ACCEPTH IMAGE PATH AS COMMAND LINE INPUT WHEN THE PROGRAM STARTS
	string userInput;
	cout << "Please input path of the image: ";
	getline(cin, userInput);
	//Read image using user provided path
	img = imread(userInput);

	//Print an error and exit if image cannot be read
	if (img.empty())
	{
		cout << "Invalid path or image file type. Please try again!" << std::endl;
		return EXIT_FAILURE;
	}
	//Check if image needs to be shrinked
	checkSize(img);

	//Present user the options to chose desired function
	int userChoice = -1;
	cout << "Please select the desired function : \n\t1: Find HSV colors of image\n\t2: Find and draw contours"
		 << "\n\t3: Detect shapes(only circle, triangle, rectangle) \nChoice: ";
	cin >> userChoice;

	Mat img_contour;
	vector<vector<Point>> contours;
	switch (userChoice)
	{
		case 1:
			findHSV(img);
			break;

		case 2:
			//Prepare image for contour detection
			img_contour = preProcessor(img);
			contours = findContours(img, img_contour);
			drawContoursLocal(img, contours);
			break;
		case 3:
			//Prepare image for shape detection
			img_contour = preProcessor(img);
			//detect shapes and show the result
			shapeDetect(img, img_contour);
			break;
		case 4:
			break;
		default:
			cout << "\nInvalid parameter. Program will now exit...";
			break;
	}
	
	

	return EXIT_SUCCESS;
}