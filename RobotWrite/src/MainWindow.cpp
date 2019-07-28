//
// Created by xy on 19-7-27.
//

#include "MainWindow.h"

void handleImage(cv::Mat &img, cv::Mat &data) {
    cv::Mat src, gray, invert;
    cv::Mat raw = img;
    assert(!raw.empty());
    cv::resize(raw, src, cv::Size(), 28.0f / raw.cols, 28.0f / raw.rows);
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    cv::bitwise_not(gray, invert);
    invert.convertTo(data, CV_32FC1, 1.0f / 255.0f);
    src.release();
    gray.release();
    invert.release();
}

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    this->resize(400, 400);

    QPushButton *predictImageBtn = new QPushButton("识别图片");
    QPushButton *cnnCameraBtn = new QPushButton("连接相机");

    auto *wholeLayout = new QVBoxLayout;

    wholeLayout->addWidget(predictImageBtn);
    wholeLayout->addWidget(cnnCameraBtn);

    setLayout(wholeLayout);

    connect(predictImageBtn, &QPushButton::clicked, this, &MainWindow::predictImage);
    connect(cnnCameraBtn,&QPushButton::clicked,this,&MainWindow::cnnCamera);
}

MainWindow::~MainWindow() {

}

void MainWindow::predictImage() {
    qDebug() << "链接成功" << endl;
    // 加载一张图片并显示
    cv::Mat img = cv::imread("/home/xy/CLionProjects/robot_write/RobotWrite/src/images/0.png");
    cv::Mat data;
    // 对图片进行处理。
    handleImage(img, data);

    cv::imshow("data", data);
    // 将data转换为tensor类型
    auto input = torch::from_blob(data.data, {1, 1, 28, 28}, at::kFloat);
    // 加载模型
    auto model = torch::jit::load("/home/xy/CLionProjects/robot_write/RobotWrite/src/mnist_cpp2.pt");
    assert(model != nullptr);
    // TODO 模型加载失败，先进行下一项。

}

void MainWindow::cnnCamera() {
    qDebug()<<"连接相机"<<endl;
    // 创建相机获取保存图片
    cnnKinect();
}
