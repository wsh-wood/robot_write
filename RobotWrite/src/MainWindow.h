//
// Created by xy on 19-7-27.
//

#ifndef ROBOT_WRITE_MAINWINDOW_H
#define ROBOT_WRITE_MAINWINDOW_H


#include <torch/torch.h>
#include <torch/script.h>
#include <iostream>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <qdebug.h>
#include <opencv2/opencv.hpp>



#include "Kinect.h"

using namespace std;

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = Q_NULLPTR);

    ~MainWindow() override;

public:
    void predictImage();
    void cnnCamera();
};


#endif //ROBOT_WRITE_MAINWINDOW_H
