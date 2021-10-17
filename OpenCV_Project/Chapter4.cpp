#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <string>


using namespace std;
using namespace cv;

//Creating images and objects with openCV

int main() {

    //Try creating a blank image
	Mat img_create(600, 600, CV_8UC3, Scalar(0, 0, 0));
    circle(img_create, Point(300, 300), 140, Scalar(255, 255, 255), FILLED);//Try drawing a circle on the canvas
    rectangle(img_create, Point(200, 250), Point(400, 350), Scalar(0,0,0), FILLED);//Draw rectangle b/w given points
    putText(img_create, "Test string", Point(220, 310), FONT_ITALIC, 1, Scalar(0, 70, 255), 2);
	imshow("Created image", img_create);//Show created image
    waitKey(0);
    return 0;
}