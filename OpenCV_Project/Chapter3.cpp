#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <string>


using namespace std;
using namespace cv;

int main() {
	string path = "Images\\img1.jpg";
	Mat img, img_resized, img_blur, img_canny;
	img = imread(path);
	//Test basic functions
	resize(img, img_resized, Size(500, 500));
	GaussianBlur(img_resized, img_blur, Size(7, 7), 5, 0);
	Canny(img_blur, img_canny, 25, 80);
	//Show the results
	imshow("Test", img_blur);
	imshow("Canny", img_canny);
	waitKey(0);
	return 0;


}