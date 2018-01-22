#ifndef __CAMERA_H
#define __CAMERA_H

#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>


// Next step is to import this into psyclone
using namespace std;
using namespace cv;


class Camera{
	// Face finder object
	public:
		int working_width, working_height;

		// Functions 
		Camera();
		Camera(int width, int height);
		~Camera();

		void show_image();
		void show_image(cv::Mat img);
		bool update_image();
		cv::Mat get_image();

	private :
		cv::VideoCapture* stream;
		double raw_width, raw_height, x_ratio, y_ratio;
		bool got_cam, got_width, working_window;
		std::vector<std::string> windows; // A vector containing the name of windows 
		cv::Mat current_frame_raw, current_frame; // Current working frame
		std::string version_number;
	
	
		
		// Functions 
		void open_stream();
//		void sleep(uint64 millis);
}; // End of Camera definition

#endif
