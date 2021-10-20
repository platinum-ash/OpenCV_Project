#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <opencv2/imgproc.hpp>

#include "image_processing.cpp"

void findHSV(Mat img);
void getContours(Mat img_dil, Mat img);
Mat preProcessor(Mat img);
void shapeDetect(Mat img, Mat img_dil);
#endif // !IMAGE_PROCESSING_H
