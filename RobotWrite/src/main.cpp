//
// Created by xy on 19-7-27.
//

#include <iostream>
#include <QApplication>
#include "MainWindow.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return QApplication::exec();

}