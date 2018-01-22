#ifndef __FACE_PROBABILTY_H
#define __FACE_PROBABILTY_H

// Stdlib
// OpenCV lib
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
// Include camera object and detection methods
#include "detector.h"


using namespace std;
using namespace cv;
// TODO: Create class so haar methods only need to be loaded once
// Have a face (cropped cv Mat, and double perc_prob)
class Face_probability{
	// Building a set of haar detectors and computing probability
	public :
		Face_probability();
		~Face_probability();
		
		Detector *A, *B, *C;
		std::vector<cv::Mat> list_of_faces();
		
		cv::Mat current_raw_input;
		void check_face(cv::Mat raw_input);
		double get_face_prob();

	private:
		bool got_face, init_params;
		double face_prob;
		bool compare_results(	std::vector<cv::Rect> const &a, 
					std::vector<cv::Rect> const &b,
					std::vector<cv::Rect> &faces,
					int work_x, int work_y,
					std::vector<double> p);
		std::vector<cv::Mat> *faces;
		double x_resize_par, y_resize_par;
		int work_x, work_y, raw_x, raw_y;
		cv::Rect resize_frame(cv::Rect input);

		void initialize_parameters(cv::Mat raw_input);
}; // End of Face_prob


double math_penilize_distance(double a, double b);
void set_text(cv::Mat &raw_input, std::string text);
int math_abs(int x);
#endif

