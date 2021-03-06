/*
Author:Epixage
This is a computer vison patern recognition for horizontal bar codes.
*/

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <cstring>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat img = imread(argv[1], -1);
	if (img.empty()) return -1;

	namedWindow("BarcodeScanner", WINDOW_AUTOSIZE);
	Mat frame, gray, bin, canny, thresh, blur, im, morphDialate, morphClose, blackhat, morphOpen;
	cv::Mat blackie = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5), cv::Point(0, 0));
	cv::Mat Morphing = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 1), cv::Point(0, 0));
	cv::Mat Opening = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(35, 23), cv::Point(0, 0));

	cv::cvtColor(frame, gray, CV_BGR2GRAY);
	cv::adaptiveThreshold(gray, bin, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 3, 3);
	cv::Canny(bin, canny, 150, 255, 3, true);
	cv::medianBlur(gray, blur, 9);

	dilate(gray, im, Mat(), Point(-1, -1), 3, 1, 1);

	morphologyEx(gray, blackhat, MORPH_BLACKHAT, blackie, Point(0, 0), 1, 1, 1);
	cv::threshold(blackhat, thresh, 5, 255, cv::THRESH_BINARY);
	morphologyEx(thresh, morphDialate, MORPH_DILATE, Morphing, Point(0, 0), 2, 1, 1);
	morphologyEx(morphDialate, morphClose, MORPH_CLOSE, Morphing, Point(0, 0), 2, 1, 1);
	morphologyEx(morphClose, morphOpen, MORPH_OPEN, Opening, Point(0, 0), 1, 1, 1);
	imshow("RGB", frame);
	imshow("Binary", bin);
	imshow("Gray", gray);
	imshow("Canny", canny);
	imshow("Thresh", thresh);
	imshow("Blur", blur);
	imshow("im", im);
	imshow("blackhat", blackhat);
	imshow("morphDilate", morphDialate);
	imshow("morphClose", morphClose);
	imshow("morphOpen", morphOpen);
}