#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include "image_processing.cpp"

void findHSV(Mat &img);
Mat preProcessor(Mat &img);
void shapeDetect(Mat &img, Mat &img_dil);
vector<vector<Point>> findContoursLocal(Mat &img_dil);
void drawContoursLocal(Mat &img, vector<vector<Point>> &contours);
#endif // !IMAGE_PROCESSING_H
