#ifndef __DETECTOR_H
#define __DETECTOR_H

// OpenCV lib
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>
#include <vector>
// Sleep function
#include <unistd.h>

using namespace std;
using namespace cv;


class Detector{
	public:
		Detector();
		Detector(std::string input_file);
		~Detector();
		void haar_detect(cv::Mat raw_input);
		void haar_detect_set_color(cv::Mat raw_input,	int b,
								int g,
								int r);
		void set_haar_file(std::string file_name);

	private:
		std::string input_file;
		cv::CascadeClassifier detect;
};// end of Detector 

#endif
