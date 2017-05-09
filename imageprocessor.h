#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include <QVector>
#include <QObject>

class ImageProcessor: public QObject
{
    Q_OBJECT

public:
    ImageProcessor();
    void fullOneFrameProcess(cv::Mat frame);
    QVector<double> plety;
    bool isface;
    int face_x;
    int face_y;
    int face_r;

signals:
    void faceIsReade(cv::Mat face);
    void numberIsReady(double intence);

private:
   // cv::VideoCapture camera;
    cv::CascadeClassifier faceHaarCascade;


    void detectFace(cv::Mat& frame);
    void findSkinRegions(cv::Mat& frame);
    cv::Mat filterSkinMask(cv::Mat& mask);
    double calculateGreenAverage(cv::Mat& frame);





};

#endif // IMAGEPROCESSOR_H
