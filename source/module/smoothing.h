#pragma once
#ifndef SMOOTHING_H
#define SMOOTHING_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/ml/ml.hpp"
class Smoothing
{
private:
	int sigmaColor, sigmaSpace;
	cv::Mat img;
	cv::Mat originalImg;
	cv::CascadeClassifier cascade;
	double scale = 1.3;

public:
	Smoothing() : sigmaColor(5), sigmaSpace(7) {}
	Smoothing(int sigmaColor, int sigmaSpace) : sigmaColor(sigmaColor), sigmaSpace(sigmaSpace) {}
	void set_sigmaColor(int sigmaColor);
	void set_sigmaSpace(int sigmaSpace);
	void init_image(std::string name);
	void init_cascade(std::string cascadeName);

	void detectAndDraw();
	void show();
	void save(std::string path);
};

#endif 