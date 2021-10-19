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
	findContours(img_dil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(0, 0, 0), 8);
	double area = 0;
	for (int i = 0; i < contours.size(); i++) {
		area = contourArea(contours[i]);

		if (area > 2500) {
			drawContours(img, contours, i, Scalar(0, 0, 0), 8);
		}
		//cout << area << endl;
	}



	imshow("Dilated image passed to the function", img_dil);
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


//Check size of image and shrink it if necessary
void checkSize(Mat &img) {
	Size img_size = img.size();
	int width = img_size.width;
	int height = img_size.height;
	if (height > 1000 || width > 1000) {
		resize(img, img, Size(800, 600));
	}
}

int main() {
	Mat img;
	//For now use console input for the image file path.
	//TODO : ACCEPTH IMAGE PATH AS COMMAND LINE INPUT WHEN THE PROGRAM STARTS
	string userInput;
	cout << "Please input path of the image: ";
	getline(cin, userInput);

	cout << "The string that was read was :  " << userInput << endl;
	//Check if image needs to be shrinked
	//string path = "Images//img6.png";
	img = imread(userInput);
	checkSize(img);

	Mat img_contour = preProcessor(img);
	getContours(img_contour, img);

	/*
	imshow("From the function", img_contour);
	waitKey(0);*/
	return EXIT_SUCCESS;
}