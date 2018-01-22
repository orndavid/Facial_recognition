#include "face_probability.h"

/*
 * Either flow :
 * 	Take in matrix return face and probability
 * 	Take in possible face, return true and probability
 */

Face_probability::Face_probability(){
	A = new Detector("haar_face.xml");
	B = new Detector("haar_face2.xml");
	C = new Detector("haar_eyes.xml");
	got_face = false;
	face_prob = 0.0;
}

Face_probability::~Face_probability(){
	// Empty	
}

double Face_probability::get_face_prob(){
	// Return probability that there is a face in the
	// figure
	if(got_face){
		got_face = false;
		return face_prob;
	}
}


void Face_probability::check_face(cv::Mat raw_input){
	// Take a raw opencv img input, check for a face 
	// and return probability that the selected frame 
	// is actually a face
	cv::Mat working_mat;

	// Compute size constants
	double par_y, par_x;
	int x = raw_input.cols;
	int y = raw_input.rows;

	// Define working size for image
	int work_x = 640;
	int work_y = 480;

	// Resize the raw input image for faster working def
	cv::resize(raw_input, working_mat, cv::Size(work_x, work_y));

	A->haar_detect_set_color(working_mat, 255,0,0);
	B->haar_detect_set_color(working_mat, 0,255,0);
	C->haar_detect_set_color(working_mat, 0,152,120);
	// TODO : crop working image set, check with haar 2
	// compare face location for probability.  
	// Ensure eyes are in image, return true false and prob
	// Draw on image to confirm.
	imshow("small", working_mat);
	// Find faces in raw input
}

