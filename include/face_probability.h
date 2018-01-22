#ifndef __FACE_PROBABILTY_H
#define __FACE_PROBABILTY_H

// OpenCV lib
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
// Include camera object and detection methods
#include "camera.h"
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
		
		void check_face(cv::Mat raw_input);
		double get_face_prob();

	private:
		bool got_face;
		double face_prob;
}; // End of Face_prob

#endif
