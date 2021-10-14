#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <string>


using namespace std;
using namespace cv;

//Just trying what diff functions do
Mat blurEdgeHighlight(Mat img, int Strength) {
	Mat final_img;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(7, 7));
	GaussianBlur(img, final_img, Size(1, 1), 3, 0);
	dilate(final_img, final_img, kernel);
	return final_img;
}


int main() {
	string path = "Images\\img1.jpg";
	Mat img, img_resized, img_blur, img_canny, img_dilated, kernel;
	img = imread(path);
	//Test basic functions
	resize(img, img_resized, Size(500, 500));
	GaussianBlur(img_resized, img_blur, Size(7, 7), 5, 0);
	Canny(img_blur, img_canny, 25, 80);
	//dilate(img_canny, img_dilated, kernel);

	//Test portrait
	imshow("Image from function", blurEdgeHighlight(img_resized, 5));
	//Show the results
	/*imshow("Test", img_blur);
	imshow("Canny", img_canny);
	imshow("Dilated", img_dilated);*/
	waitKey(0);
	return 0;


}