#include <iostream>
#include "smoothing.h"

void Smoothing::set_fSize(int fSize) { this->fSize = fSize; }
void Smoothing::set_sigma(int sigma) { this->sigma = sigma; }
int Smoothing::get_fSize() { return this->fSize; }
int Smoothing::get_sigma() { return this->sigma; }
void Smoothing::init_image(std::string name)
{
    img = cv::imread(name);
    img.copyTo(originalImg);
}
void Smoothing::init_cascade(std::string cascadeName)
{
    if (!cascade.load(cascadeName))
    {
        std::cerr << "ERROR: Could not load classifier cascade" << std::endl;
    }
}

void Smoothing::detectAndDraw()
{
    originalImg.copyTo(img);

	int i = 0;
	double t = 0;
	std::vector<cv::Rect> faces;
	const static cv::Scalar colors[] = { CV_RGB(0,0,255),
		CV_RGB(0,128,255),
		CV_RGB(0,255,255),
		CV_RGB(0,255,0),
		CV_RGB(255,128,0),
		CV_RGB(255,255,0),
		CV_RGB(255,0,0),
		CV_RGB(255,0,255) };

	cv::Mat gray, smallImg(cvRound(img.rows / scale), cvRound(img.cols / scale), CV_8UC1);

	cvtColor(img, gray, cv::COLOR_BGRA2GRAY);
	resize(gray, smallImg, smallImg.size(), 0, 0, cv::INTER_LINEAR);
	equalizeHist(smallImg, smallImg);

	cascade.detectMultiScale(smallImg, faces,
		1.1, 2, 0
		//|CV_HAAR_FIND_BIGGEST_OBJECT
		//|CV_HAAR_DO_ROUGH_SEARCH
		| cv::CASCADE_SCALE_IMAGE
		,
		cv::Size(30, 30));

	for (std::vector<cv::Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++)
	{
		cv::Mat smallImgROI;
		std::vector<cv::Rect> nestedObjects;
		cv::Point center, left, right;
		cv::Scalar color = colors[i % 8];
		int radius;
		center.x = cvRound((r->x + r->width * 0.5) * scale);
		center.y = cvRound((r->y + r->height * 0.5) * scale);
		radius = cvRound((r->width + r->height) * 0.25 * scale);


		left.x = center.x - radius;
		left.y = cvRound(center.y - radius * 1.3);

		if (left.y < 0)
		{
			left.y = 0;
		}

		right.x = center.x + radius;
		right.y = cvRound(center.y + radius * 1.3);

		if (right.y > img.rows)
		{
			right.y = img.rows;
		}

		rectangle(img, left, right, cv::Scalar(255, 0, 0));

		
		cv::Mat roi = img(cv::Range(left.y, right.y), cv::Range(left.x, right.x));
		cv::Mat dst;

		int value1 = this->fSize, value2 = this->sigma;

		int dx = value1 * 5;    
		double fc = value1 * 12.5;
		int p = 50;
		cv::Mat temp1, temp2, temp3, temp4;


		bilateralFilter(roi, temp1, dx, fc, fc);

		temp2 = (temp1 - roi + 128);


		GaussianBlur(temp2, temp3, cv::Size(2 * value2 - 1, 2 * value2 - 1), 0, 0);

		temp4 = roi + 2 * temp3 - 255;

		dst = (roi * (100 - p) + temp4 * p) / 100;


		dst.copyTo(roi);
	}
}
void Smoothing::show()
{
    cv::namedWindow("Smoothed");
    cv::imshow("Smoothed", img);
    cv::waitKey(0);
    cv::destroyAllWindows();
}
void Smoothing::save(std::string path) { cv::imwrite(path, img); }
