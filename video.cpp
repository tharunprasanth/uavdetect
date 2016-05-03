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
//void detectAndDisplay(Mat frame);

void detectAndDisplay();
/** Global variables */
//-- Note, either copy these two files from opencv/data/haarscascades to your current folder, or change these locations
String flight_cascade_name = "cascade.xml";
CascadeClassifier flight_cascade;
string window_name = "Amazon Prime Air Ad";
RNG rng(12345);
Mat frame;
/**
 * @function main
 */
int main(void)
{
	VideoCapture capture("out.mp4");
//	Mat frame;
	//-- 1. Load the cascades
	if (!flight_cascade.load(flight_cascade_name)) {
		printf("--(!)Error loading\n");
		return -1;
	};

	//-- 2. Read the video stream
	if (capture.isOpened()) {
		double total_time = 0.0;
		int c, cpt = 30;

		double t = (double)cv::getTickCount();
		for (;;) {
			t = ((double)cv::getTickCount() -
			     t) / cv::getTickFrequency();
			total_time += t;
			cpt++;
			t = (double)cv::getTickCount();
			capture.read(frame);
			//-- 3. Apply the classifier to the frame
			if (!frame.empty()) {
				cv::putText(frame,
					    cv::format("Average FPS=%d",
						       cvRound(cpt /
							       total_time)),
					    cv::Point(30, 30),
					    cv::FONT_HERSHEY_SIMPLEX, 1.0,
					    cv::Scalar(0, 0, 255));
					
				imshow(window_name, frame);
				//detectAndDisplay(frame);
				detectAndDisplay();
				
			} else {
				printf(" --(!) No captured frame -- Break!");
				break;
			}

			int c = waitKey(20);
			if ((char)c == 'c') {
				break;
			}

		}
	}
	return 0;
}

/**
 * @function detectAndDisplay
 */
//void detectAndDisplay(Mat frame)

void detectAndDisplay()
{
	std::vector < Rect > flight;
	Mat frame_gray;
	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
	//-- Detect faces
	flight_cascade.detectMultiScale(frame_gray, flight, 1.1, 2,
					0 | CV_HAAR_SCALE_IMAGE, Size(100,
								      100));

	for (size_t i = 0; i < 1; i++) {
		Point center(flight[i].x + flight[i].width / 2,
			     flight[i].y + flight[i].height / 2);
		rectangle(frame, cvPoint(flight[i].x, flight[i].y),
			  cvPoint(flight[i].x + flight[i].width,
				  flight[i].y + flight[i].height), Scalar(0, 0,
									  255),
			  2);
		putText(frame, "Quad", cvPoint(flight[i].x, flight[i].y),
			FONT_HERSHEY_PLAIN, 1.0, Scalar(255, 0, 0), 2.0);
		//Mat faceROI = frame_gray( faces[i] );

		//-- In each face, detect eyes

	}
	//-- Show what you got
	imshow(window_name, frame);
}
