#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <opencv2/imgproc.hpp>

#include "Source.cpp"

void findHSV(Mat img);
void getContours(Mat img_dil, Mat img);
Mat preProcessor(Mat img);

#endif // !IMAGE_PROCESSING_H
