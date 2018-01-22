#include "face_probability.h"

#include "opencv2/core.hpp"                                                      
#include "opencv2/opencv.hpp"                                                    
#include "opencv2/highgui.hpp"   

using namespace std;

int main(){
	std::string face_file = "haar_face.xml";
	// currently set at *frontalface_alt.xml 
	std::string face2_file = "haar_face2.xml";
	// currently set at *forntalface_alt2.xml
	std::string eyes_file = "haar_eyes.xml";
	// currently set at *eye.xml
	Camera obj(1920, 1080);
	Face_probability face_scanner;

	while(true){
		if(obj.update_image()){
			face_scanner.check_face(obj.get_image());
			obj.show_image(obj.get_image());
		}else{
			break;
		}
	}
	return 0;
}
