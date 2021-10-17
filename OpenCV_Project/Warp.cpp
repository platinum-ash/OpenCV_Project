#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <string>



using namespace std;
using namespace cv;

//Change perspective of an image
//test with cards, coverting a card to birds eye view. The last card to the right is the one being transformed

int main() {
	float width, height;
	width = 300.0f;
	height = 400.0f;
	string path = "Images//img2.jpg";
	Mat img = imread(path);
	Mat transformed, img_out;

	Point2f transform_src[4] = {{791, 145}, {1027, 234}, {660, 450}, {930, 566}};//Coordinates of the last card i.e ace
	Point2f transform_dst[4] = {{0.0f, 0.0f}, {width, 0.0f}, {0.0f, height}, {width, height}};

	transformed = getPerspectiveTransform(transform_src, transform_dst);
	warpPerspective(img, img_out, transformed, Point(width, height));

	//Highlight points to better show where the image for change of perspective is being extracted from
	for (int i = 0; i < 4; i++) {
		circle(img, transform_src[i], 8, Scalar(0, 70 ,255), FILLED);
	}

	imshow("Changed perspective", img_out);//Show extracted and changed perspective image of the single card
	imshow("Original image", img);
	waitKey(0);
	return 0;
}