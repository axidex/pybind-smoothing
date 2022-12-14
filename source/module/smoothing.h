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
	int fSize;
	double sigma;
	cv::Mat img;
	cv::Mat originalImg;
	cv::CascadeClassifier cascade;
	double scale = 1.3;

public:
	Smoothing() : fSize(5), sigma(7) {}
	Smoothing(int fSize, int sigma) : fSize(fSize), sigma(sigma) {}
	int get_fSize();
	int get_sigma();
	void set_fSize(int fSize);
	void set_sigma(int sigma);
	void init_image(std::string name);
	void init_cascade(std::string cascadeName);

	void detectAndDraw();
	void show();
	void save(std::string path);
};

#endif 