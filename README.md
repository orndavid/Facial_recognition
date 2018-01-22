# Facial_recognition
Opencv facial recognition

Using opencv Haar detection methods to find a person in an image, double
check that there is a person in the image by using the following setup

	Haar face detector A -> Resized raw image
	Haar face detector B-> Resized raw image
	Haar eye detector  -> Cropped raw image with faces.

Return the probability that there is a face by comparing the output 
rectangles of face detectors A and B;

The Haar cascade files used are from the opencv dataset of haar cascades
the original file names are
		haar_face.xml = haarcascade_frontalface_alt.xml
		haar_face2.xml=haarcascade_frontalface_alt2.xml
		haar_eyes.xml =haarcascade_eyes.xml 
