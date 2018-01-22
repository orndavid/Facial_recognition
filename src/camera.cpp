#include "camera.h"

using namespace std;
using namespace cv;

Camera::Camera(){
	// Constructor for object
	open_stream();
	cout << "New Camera object created" << endl;
	working_window = false;
	cout << "Current raw output" << endl;
	std::printf("Input resolution : %u x %u ", 
			(int)stream->get(CV_CAP_PROP_FRAME_WIDTH),
			(int)stream->get(CV_CAP_PROP_FRAME_HEIGHT));
}

Camera::Camera(int width, int height){
	open_stream();
	stream->set(CV_CAP_PROP_FRAME_WIDTH, width);
	stream->set(CV_CAP_PROP_FRAME_HEIGHT, height);
	cout << "Current raw output" << endl;
	std::printf("Input resolution : %u x %u ", 
			(int)stream->get(CV_CAP_PROP_FRAME_WIDTH),
			(int)stream->get(CV_CAP_PROP_FRAME_HEIGHT));
}

Camera::~Camera(){
	// Destroy open windows
	std::vector<std::string>::iterator iter;
	for(iter=windows.begin(); iter!=windows.end(); iter++){  
		cout << "Destroying window :" << *iter << endl;
		cv::destroyWindow(*iter);
	}
	cout << "Destroying Stream" << endl;
	delete stream;
}

void Camera::show_image(){
	if(got_cam){
		cv::namedWindow("raw capture", 
				CV_WINDOW_AUTOSIZE);
		windows.push_back("raw_capture");
		while(1){
			if(stream->read(current_frame_raw)){
				imshow("raw_capture",current_frame_raw);
			}
			if(cv::waitKey(30)==27){
				cout << "User terminated with esc" << endl;
				break;
			}
		}
	}
}

bool Camera::update_image(){
	if(stream->read(current_frame_raw)){
		if(cv::waitKey(30)==27){
			cout << "User terminated with esc" << endl;
			stream->release();
			
		}
		return true;
	}else
		return false;


}

void Camera::open_stream(){
	version_number = CV_VERSION;
	stream = new cv::VideoCapture(CV_CAP_ANY);

	if(!stream->isOpened()){
		cout << "Unable to open camera stream" <<endl;
		got_cam = false;
	}
	else{
		cout << "Got camera input" << endl;
		std::printf("Input resolution : %u x %u ", 
			   	(int)stream->get(CV_CAP_PROP_FRAME_WIDTH),
				(int)stream->get(CV_CAP_PROP_FRAME_HEIGHT));
	}
}


cv::Mat Camera::get_image(){
	return  current_frame_raw;
}


void Camera::show_image(cv::Mat img){
	if(working_window == false){
		working_window = true;
		windows.push_back("Working window");
	}
	else{
		cv::imshow("Working window", img);
	}
}
