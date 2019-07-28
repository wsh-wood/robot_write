//
// Created by xy on 19-7-27.
//

#include "Kinect.h"

void cnnKinect() {

    //! [context]
    libfreenect2::Freenect2 freenect2;
    libfreenect2::Freenect2Device *dev = nullptr;
    libfreenect2::PacketPipeline *pipeline = nullptr;
    //! [context]
    //! [discovery]

    std::cout <<"device === " <<freenect2.enumerateDevices() << std::endl;
    if(freenect2.enumerateDevices() == 0)
    {
        std::cout << "no device connected!" << std::endl;
//        return -1;
    }
    std::string serial = freenect2.getDefaultDeviceSerialNumber();
//    if(serial == "")  return -1;
    cout<<"The serial number is :"<<serial<<endl;
    //! [discovery]

    pipeline = new libfreenect2::OpenGLPacketPipeline();

    dev = freenect2.openDevice(serial, pipeline);

    //! [listeners]
    libfreenect2::SyncMultiFrameListener listener(libfreenect2::Frame::Color |libfreenect2::Frame::Depth);
    libfreenect2::FrameMap frames;
    dev->setColorFrameListener(&listener);
    dev->setIrAndDepthFrameListener(&listener);
    //! [listeners]

    //! [start]
    cout<<"start1"<<endl;


    dev->start();
    cout<<"start2"<<endl;




    std::cout << "device serial: " << dev->getSerialNumber() << std::endl;
    std::cout << "device firmware: " << dev->getFirmwareVersion() << std::endl;

    libfreenect2::Registration *registration = new libfreenect2::Registration(dev->getIrCameraParams(),
                                                                              dev->getColorCameraParams());
    Mat rgbmat;

    listener.waitForNewFrame(frames);
    libfreenect2::Frame *rgb = frames[libfreenect2::Frame::Color];

    // 这里是获取深度图。
    // libfreenect2::Frame *depth = frames[libfreenect2::Frame::Depth];

    rgbmat = Mat(rgb->height, rgb->width, CV_8UC4, rgb->data);

    imshow("rgb", rgbmat);
    // TODO 对图片进行裁剪，降噪，旋转等操作。然后保存。

    stringstream rr;
    rr << "/home/xy/CLionProjects/robot_write/Test/src/cameraImage/camera_image.jpg";
    vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);  //选择jpeg
    compression_params.push_back(100); //在这个填入你要的图片质量
    cv::imwrite(rr.str(), rgbmat, compression_params);
    cout << rr.str() << endl;

    dev->stop();
    dev->close();

    delete registration;

    std::cout << "Goodbye World!" << std::endl;

};