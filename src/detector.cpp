#include "detector.h"

Detector::Detector(){
	// Empty
}
Detector::Detector(std::string input_file){
	input_file = input_file;
	unsigned int microsecs = 200;
	usleep(microsecs);
	if(!detect.load(input_file)){
		cout << "Found haar file:" << input_file << endl;
	}
	else{
		cout << "Unable to find Haar file: " << input_file << endl;
	}
}

Detector::~Detector(){
	// Empty
}

void Detector::set_haar_file(std::string input_file){
	input_file = input_file;
	unsigned int microsecs = 200;
	usleep(microsecs);
	if(!detect.load(input_file)){
		cout << "Found haar file:" << input_file << endl;
	}
	else{
		cout << "Unable to find Haar file: " << input_file << endl;
	}
}

void Detector::haar_detect(cv::Mat raw_input){
	// Find a face in the raw_input file
	std::vector<cv::Rect> found;

	detect.detectMultiScale(raw_input, found,1.1, 2, 0 |
				CASCADE_SCALE_IMAGE, 
				cv::Size(50, 50));

	if(found.size() > 0){
		for(auto const &box: found){
			cv::rectangle(raw_input, box, cv::Scalar(0,255,0));
		}
	}
}

void Detector::haar_detect_set_color(cv::Mat raw_input, int r, int g, int b){
	// Find defined object in image and draw with colors defined 
	std::vector<cv::Rect> found;
	detect.detectMultiScale(raw_input, found,1.1, 2, 0 |
				CASCADE_SCALE_IMAGE, 
				cv::Size(50, 50));

	if(found.size() > 0){
		for(auto const &box: found){
			cv::rectangle(raw_input, box, cv::Scalar(r,g,b));
		}
	}
}

std::vector<cv::Rect> Detector::detect_obj(cv::Mat &raw_input){
	// Return set of found vectors with rectangle type
	std::vector<cv::Rect> found;
	detect.detectMultiScale(raw_input, found,1.1, 2, 0 |
				CASCADE_SCALE_IMAGE, 
				cv::Size(50, 50));

	if(found.size() > 0){
		return found;
	}
}
