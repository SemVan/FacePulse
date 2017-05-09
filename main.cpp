#include "mainwindow.h"
#include <QApplication>
#include <opencv2/core/core.hpp>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    try {

    w.show();
    return a.exec();
    }
    /*catch (std::exception &e){
       std::cout<<"FUCK"<<e.what()<<std::endl;
        //QMessageBox newBox("fuck","fuckmotherfuck");

        return 1;
    }*/
    catch (cv::Exception &e) {
        std::cout<<"FUCK"<<std::endl;

        return 1;
    }



}
