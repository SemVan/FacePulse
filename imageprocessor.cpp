#include "imageprocessor.h"
#include "QMessageBox"

#define MINIMUM_FACE_SIZE 250

ImageProcessor::ImageProcessor()
{
    isface = 0;
    faceHaarCascade.load("C:///Coding///Cascades//haarcascade_frontalface_alt.xml");

}


void ImageProcessor::fullOneFrameProcess(cv::Mat frame) {
    cv::Mat faceEbat;

    detectFace(frame);
    //findSkinRegions(faceEbat);
    if(isface) {
        numberIsReady(calculateGreenAverage(frame));
    }

}

void ImageProcessor::detectFace(cv::Mat& frame) {

    std::vector<cv::Rect> faces;
    if (faceHaarCascade.empty()) {
        isface=0;
        return;
    }
    faceHaarCascade.detectMultiScale( frame, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(MINIMUM_FACE_SIZE, MINIMUM_FACE_SIZE) );

    if (faces.size()) {
        face_x = faces[0].x;
        face_y = faces[0].y;
        face_r = faces[0].width;
        isface = 1;
        frame=frame(faces[0]);
     } else {
        isface = 0;
    }

}

void ImageProcessor::findSkinRegions(cv::Mat& frame) {
    int lowR=0;
    int lowB=48;
    int lowG=80;

    int highR=20;
    int highB=255;
    int highG=255;

    cv::Mat converted;
    cv::cvtColor(frame,converted,CV_BGR2HSV);

    cv::Mat skinMask;
    cv::inRange(converted, cv::Scalar(lowR, lowB, lowG),cv::Scalar(highR, highB, highG), skinMask);
    skinMask=filterSkinMask(skinMask);

    cv::Mat finalImage;
    frame.copyTo(finalImage,skinMask);

}


cv::Mat ImageProcessor::filterSkinMask(cv::Mat& mask) {
    cv::Mat newMask;
    cv::Mat kernel=cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(11,11));
    cv::erode(mask,newMask,kernel);
    cv::dilate(newMask,newMask,kernel);
    return newMask;
}

double ImageProcessor::calculateGreenAverage(cv::Mat& frame) {
    cv::Mat colors[3];
    cv::split(frame,colors);

    double aver=0;
    for (int i=0; i<colors[1].cols; i++) {
        for (int j=0; j<colors[1].rows; j++) {
            aver += colors[1].at<uchar>(i,j);
        }
    }

    return aver;
}
