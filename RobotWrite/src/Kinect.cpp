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

    std::cout << "device === " << freenect2.enumerateDevices() << std::endl;
    if (freenect2.enumerateDevices() == 0) {
        std::cout << "no device connected!" << std::endl;
//        return -1;
    }
    std::string serial = freenect2.getDefaultDeviceSerialNumber();
//    if(serial == "")  return -1;
    cout << "The serial number is :" << serial << endl;
    //! [discovery]

    pipeline = new libfreenect2::OpenGLPacketPipeline();

    dev = freenect2.openDevice(serial, pipeline);

    //! [listeners]
    libfreenect2::SyncMultiFrameListener listener(libfreenect2::Frame::Color | libfreenect2::Frame::Depth);
    libfreenect2::FrameMap frames;
    dev->setColorFrameListener(&listener);
    dev->setIrAndDepthFrameListener(&listener);
    //! [listeners]

    //! [start]
    cout << "start1" << endl;


    dev->start();
    cout << "start2" << endl;

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
    cv::imshow("rgbmat",rgbmat);

    //  对图片进行裁剪，降噪，旋转等操作。然后保存。
    // rgbmat = dealImage(rgbmat);
/*    // 首先加载获取好的图片并显示。
    cv::Mat raw = img;*/
    // 首先对图像进行灰度处理
    cv::Mat gray;
    //cv::imshow("raw",raw);
    // TODO 此处还需优化
    cv::Rect rect(700, 200, 650, 600);
    cv::cvtColor(rgbmat, gray, cv::COLOR_BGR2GRAY);
    cout<<"hello"<<endl;
    gray = gray(rect);
    cv::imshow("gray",gray);
    // canny边缘检测
    cv::Mat canny;
    cv::Canny(gray, canny, 10, 255, 3, false);
    // cv::imshow("canny",canny);
    // 用矩形检测
    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierachy;

    cv::findContours(canny, contours, hierachy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
    cv::Mat dst = cv::Mat::zeros(canny.size(), canny.type());

    cv::drawContours(dst, contours, -1, cv::Scalar(255, 0, 0));
    vector<vector<cv::Point>> newContours;
    cv::Mat newdst = cv::Mat::zeros(canny.size(), canny.type());
    // 矩形检测
    for (int i = 0; i < contours.size(); ++i) {
        vector<cv::Point> c = contours[i];
        double c_len = cv::arcLength(c, true);
        vector<cv::Point> c2;
        cv::approxPolyDP(c, c2, 0.02 * c_len, true);
        int a = c2.size();
        double b = cv::contourArea(c2);

        if (a == 4 && b > 30000.0 && cv::isContourConvex(c2)) {
            newContours.push_back(c2);
        }
    }

    cv::drawContours(newdst, newContours, -1, cv::Scalar(255, 0, 0));
    // cv::imshow("dst",newdst);
    // 依据检测出的轮廓角点再次提取ROI
    int val = 30;
    for (int j = 0; j < newContours.size(); ++j) {
        cout<<newContours[j]<<endl;
    }
    cv::Rect rect2(newContours[0][0].x, newContours[0][0].y, 230, 260);
    // 对灰度图再次裁剪
    gray = gray(rect2);
    //cv::imshow("gray",gray);
    // 对图片进行旋转
    cv::flip(gray, gray, 1);
    // 形态学腐蚀，利用更好的检测。
    int s = 11;
    cv::Mat structureElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(s, s), cv::Point(-1, -1));
    // cv::dilate(binary,binary,structureElement,cv::Point(-1,-1),1);
    cv::erode(gray, gray, structureElement);

    // 对图片进行二值化处理。
    cv::Mat binary;
    cv::threshold(gray, binary, 230, 255, cv::THRESH_BINARY);

    // 降噪
    int s2 = 15;
    cv::Mat structureElement2 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(s2, s2), cv::Point(-1, -1));
    cv::morphologyEx(binary, binary, cv::MORPH_OPEN, structureElement2, cv::Point(-1, -1), 1);

    //cv::imshow("binary", binary);

    // 缩放图片与归一化。
    cv::resize(binary, binary, cv::Size(), 28.0f / binary.cols, 28.0f / binary.rows);

    binary.convertTo(binary, CV_32FC3, 1.0f / 255.0f);

    //cv::imshow("dst",binary);

    // TODO 识别图像
    // 将data转换为tensor类型
    auto input = torch::from_blob(binary.data, {1, 1, 28, 28}, at::kFloat);
    // 加载模型
    auto model = torch::jit::load("/home/xy/CLionProjects/robot_write/RobotWrite/src/trace_cpp.pt");
    assert(model != nullptr);
    // TODO 模型加载失败，先进行下一项。
    auto output = at::softmax(model->forward({input}).toTensor(), 1);
    auto pred = at::argmax(output, 1, true);
    auto label = pred.item<int64_t>();
    auto prob = output[0][label].item<float_t>();
    std::cout << "label: " << label << " (prob: " << prob << ")" << std::endl;

    cv::waitKey(0);
    cv::destroyAllWindows();
    // TODO 加载图片判断,if (label == 0){ 机器人在指定移动，画一个0 }

    rgbmat.release();

    dev->stop();
    dev->close();

    delete registration;

    std::cout << "Goodbye World!" << std::endl;

};