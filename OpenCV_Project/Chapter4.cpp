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
	Mat img_create(600, 550, CV_8UC3, Scalar(100, 0, 0));
	imshow("Created image", img_create);//Show created image
    waitKey(0);
    return 0;
}