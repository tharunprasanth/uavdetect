cmake_minimum_required(VERSION 2.8)
project( flightdetect )
find_package( OpenCV REQUIRED )
add_executable( flightdetector uavdetect.cpp )
target_link_libraries( flightdetector ${OpenCV_LIBS} )

add_executable( flightdetector_video video.cpp )
target_link_libraries( flightdetector_video ${OpenCV_LIBS} )
