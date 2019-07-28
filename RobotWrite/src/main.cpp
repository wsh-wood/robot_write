//
// Created by xy on 19-7-28.
//
#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}
