#include "face_probability.h"
#include "camera.h"

using namespace std;

int main(){
	Camera obj(1920, 1080);
	Face_probability face_scanner;

	while(true){
		if(obj.update_image()){
			face_scanner.check_face(obj.get_image());
		}else{
			break;
		}
	}
	return 0;
}

