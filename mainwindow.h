#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "QElapsedTimer"
#include "qcustomplot.h"
#include "imageprocessor.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include "keepncalc.h"
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void connectSignalNSlots();
    void setGraphicsForForm();
    void setGraphicsForPlots(QCustomPlot *customPlot);
    Ui::MainWindow *ui;
    QTimer dataTimer;
    cv::VideoCapture camera;
    cv::CascadeClassifier faceHaarCascade;
    bool isnorm;
    int pulse;
    ImageProcessor my;
    QElapsedTimer ellapser;
    KeepNcalc calc;
    double pulse_norm;
    int count_of_frames_processed;
    QImage face;
    QCPBars *bars1;

    void savePdfReport();


private slots:
    void newNumberCame(double num);

    void Runcam();
    void on_pushButton_clicked();
    void Run(QCustomPlot *customPlot);
    void pushNew();
    void on_pushButton_2_clicked();
    QImage putImage(const cv::Mat& mat);
    void pasteim();

    void on_pushButton_3_clicked();
    void calc_started();
    void collect_started();
    void showHeartRate(double heartRate);
};

#endif // MAINWINDOW_H
