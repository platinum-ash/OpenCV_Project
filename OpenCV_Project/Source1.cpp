#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <string>



using namespace std;
using namespace cv;



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

/****
*	checkSize;
*	Check size of image and shrink it if necessary
*	Arguments: Image of type Mat passed by reference
*	Returns: void
*****/
//
void checkSize(Mat &img) 
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
		cout << "Invalid path or image file type. Please try again!" << endl;
		return EXIT_FAILURE;
	}
	//Check if image needs to be shrinked
	checkSize(img);
	//Prepare image for contour detection
	Mat img_contour = preProcessor(img);
	//Add contours and show the result
	getContours(img_contour, img);

	return EXIT_SUCCESS;
}