//
// Created by xy on 19-7-27.
//

#ifndef ROBOT_WRITE_KINECT_H
#define ROBOT_WRITE_KINECT_H

#include <iostream>
#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/registration.h>
#include <libfreenect2/packet_pipeline.h>
#include <libfreenect2/logger.h>

#include <opencv2/opencv.hpp>
#include <sstream>
#include <cstdlib>

using namespace std;
using namespace cv;

void cnnKinect();


#endif //ROBOT_WRITE_KINECT_H
