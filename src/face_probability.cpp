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
	init_params = false;
	face_prob = 0.0;
}

Face_probability::~Face_probability(){
	// Empty	
}

void Face_probability::initialize_parameters(cv::Mat raw_input){
	// Compute size constants
	double par_y, par_x;
	raw_x = raw_input.cols;
	raw_y = raw_input.rows;

	// Define working size for image
	work_x = 640;
	work_y = 480;
	x_resize_par = raw_x/work_x;
	y_resize_par = raw_y/work_y;

	init_params = true;
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
	current_raw_input = raw_input;
	// Take a raw opencv img input, check for a face 
	// and return probability that the selected frame 
	// is actually a face
	cv::Mat working_mat;

	if(!init_params)
		initialize_parameters(raw_input);


	// Resize the raw input image for faster working def
	cv::resize(raw_input, working_mat, cv::Size(work_x, work_y));
	std::vector<cv::Rect> res_a, res_b, res_c, faces, eyes;

	
	res_a = A->detect_obj(working_mat);
	res_b = B->detect_obj(working_mat);
	std::vector<double> probability_face;
	
	if(compare_results(res_a, res_b, faces, work_x, 
			   work_y, probability_face)){
		int counter = 0;
		for(auto const &face : faces){
			cv::Mat temp;
			raw_input(resize_frame(face)).copyTo(temp);
			res_c = C->detect_obj(temp);
			if(res_c.size() == 2){
				for(auto const &rects : res_c){
					rectangle(temp, rects, 
						cv::Scalar(255,255,25));
					imshow("Cropped", temp);
				}
			}
		}
	}

}

bool Face_probability::compare_results(	std::vector<cv::Rect> const &inp_a, 
					std::vector<cv::Rect> const &inp_b,
					std::vector<cv::Rect> &faces,
					int work_x, int work_y,
					std::vector<double> p){
	// Take in two vectors with data, a and b, compare the datasets
	// A->B, see if there are overlapping values, if overlapping value
	// return the faces that overlap in std::vector faces
	
	// Size variables	
	bool ans = false;
	double diff_x, diff_y, diff_h, diff_w, area_a, area_b, alpha1,
	       dx, dy, alpha; 
	for(auto const &img : inp_a){
		cv::rectangle(current_raw_input, resize_frame(img),
				cv::Scalar(255,0,0));
		area_a = img.width*img.height;
		for(auto const &img2 : inp_b){
			rectangle(current_raw_input, resize_frame(img2), 
					cv::Scalar(255,0,0));
			area_b = img2.width*img2.height;
			if (area_a > area_b)
				alpha1 = area_b/area_a;

			diff_h = math_abs(img.y-img2.y);
			diff_w = math_abs(img.x-img2.x);
			dx = math_penilize_distance(diff_w, work_x);
			dy = math_penilize_distance(diff_h, work_y);
			alpha = alpha1 * (1-dx)*(1-dy);
			if(alpha > .90){
				ans = true;
				faces.push_back(img);
				p.push_back(alpha);
				// Debug, print text and show image in figure
				imshow("Caught face", current_raw_input);
				cout << "Face probability: " << alpha  <<endl;

			}
		}
	}
	return ans;
}

double math_penilize_distance(double a, double b){
	// Compute a simple function with 
	// penalty for distance. 
	double out = a/b * 3;
	if(a > b/3)
		return 1;
	return out;
}

int math_abs(int x){
	if(x < 0)
		return -x;
	return x;
}

cv::Rect Face_probability::resize_frame(cv::Rect input){
	// Resize a frame from working size to fit raw size
	// used to move from face detection to eye detection.
	// Face detection uses small resized matrix to work on
	// eyes use cropped image from raw_input
	int x = input.x*x_resize_par;
	int y = input.y*y_resize_par+75;
	int width = input.width*x_resize_par;
	int height = input.height*x_resize_par*1.25;

	if((x+width) > raw_x)
		width = raw_x-x;
	if((y+height) > raw_y)
		height = raw_y-y;
	return cv::Rect(x, y, width, height);
}
