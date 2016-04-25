/**
 * @file objectDetection.cpp
 * @author A. Huaman ( based in the classic facedetect.cpp in samples/c )
 * @brief A simplified version of facedetect.cpp, show how to load a cascade classifier and how to find objects (Face + eyes) in a video stream
 */
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay(Mat frame);

/** Global variables */
//-- Note, either copy these two files from opencv/data/haarscascades to your current folder, or change these locations
String flight_cascade_name = "cascade.xml";
CascadeClassifier flight_cascade;
RNG rng(12345);

/**
 * @function main
 */
int main(int argc, char **argv)
{
	VideoCapture capture;

	//-- 1. Load the cascades
	if (!flight_cascade.load(flight_cascade_name)) {
		printf("-- (!)Error loading \ n ");
		return -1;
	};

	if (argc != 2) {
		cout << " Usage:display_image ImageToLoadAndDisplay " << endl;
		return -1;
	}

	Mat image;
	image = imread(argv[1], CV_LOAD_IMAGE_COLOR);	// Read the file

	if (!image.data)	// Check for invalid input
	{
		cout << " Could not open or find the image " << std::endl;
		return -1;
	}
	detectAndDisplay(image);
	return 0;
}

/**
 * @function detectAndDisplay
 */
void detectAndDisplay(Mat image)
{
	std::vector < Rect > flight;
	Mat image_gray;

	cvtColor(image, image_gray, COLOR_BGR2GRAY);
	equalizeHist(image_gray, image_gray);
	//-- Detect faces
	flight_cascade.detectMultiScale(image_gray, flight, 1.1, 2,
					0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

	for (size_t i = 0; i < flight.size(); i++) {
                Point center( flight[i].x + flight[i].width/2, flight[i].y + flight[i].height/2 );
		rectangle( image, cvPoint(flight[i].x, flight[i].y), cvPoint(flight[i].x + flight[i].width, flight[i].y + flight[i].height), Scalar(0,0,255),1,8,0);
		Mat faceROI = image_gray(flight[i]);
		printf("\n\n success");
	}
	//-- Show what you got
	namedWindow(" Display window ", WINDOW_AUTOSIZE);	// Create a window for display.
	imshow(" Display window ", image);
	waitKey(0); 
}
