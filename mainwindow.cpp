#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parcer1.h"
#include "QObject"
#include "QString"
#include "string.h"
#include "imageprocessor.h"
#include "ctime"
#include "cmath"
#include "saver.h"
#include "QElapsedTimer"
#include "QDebug"
#include "QImage"
#define ONE_POINT_OF_DROWING  360.0/523.0
#define FRAMES 523



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    isnorm(0),
    pulse(0),
    count_of_frames_processed(0)
{


    ui->setupUi(this);

    setGraphicsForForm();
    connectSignalNSlots();




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectSignalNSlots() {
    connect(&dataTimer, SIGNAL(timeout()),this,SLOT(pasteim()));
    QObject::connect(&my,SIGNAL(numberIsReady(double)),this,SLOT(newNumberCame(double)));
    QObject::connect(&calc,SIGNAL(calculating()),this,SLOT(calc_started()));
    QObject::connect(&calc,SIGNAL(data_collect()),this,SLOT(collect_started()));
    QObject::connect(&calc,SIGNAL(rateIsReady(double)),this,SLOT(showHeartRate(double)));
}

void MainWindow::setGraphicsForForm() {

    face.load("1.png","PNG");

   this->setStyleSheet("background-color: rgba(30,30,30,255);");
    ui->pushButton->setStyleSheet("background-color:rgba(70,70,70,255);");
    ui->pushButton_2->setStyleSheet("background-color:rgba(70,70,70,255);");
    ui->pushButton_3->setStyleSheet("background-color:rgba(70,70,70,255);");

    ui->lcdNumber->setStyleSheet("color: rgba(255,153,0,255);");

   setGraphicsForPlots(ui->widget);
   setGraphicsForPlots(ui->widget_2);

   bars1 = new QCPBars(ui->widget_2->xAxis, ui->widget_2->yAxis);
   bars1->setPen(Qt::NoPen);
   bars1->setBrush(QColor(255, 153, 0, 255));


}

void MainWindow::setGraphicsForPlots(QCustomPlot *customPlot) {
    customPlot->setInteraction(QCP::iRangeDrag,true);
    customPlot->setInteraction(QCP::iRangeZoom,true);
    customPlot->addGraph();

    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(QColor(255, 153, 0, 255)), 9));

    customPlot->xAxis->grid()->setLayer("belowmain");
    customPlot->yAxis->grid()->setLayer("belowmain");

     customPlot->xAxis->setBasePen(QPen(Qt::white, 1));
     customPlot->yAxis->setBasePen(QPen(Qt::white, 1));
     customPlot->xAxis->setTickPen(QPen(Qt::white, 1));
     customPlot->yAxis->setTickPen(QPen(Qt::white, 1));
     customPlot->xAxis->setSubTickPen(QPen(Qt::white, 1));
     customPlot->yAxis->setSubTickPen(QPen(Qt::white, 1));
     customPlot->xAxis->setTickLabelColor(Qt::white);
     customPlot->yAxis->setTickLabelColor(Qt::white);
     customPlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
     customPlot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
     customPlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
     customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
     customPlot->xAxis->grid()->setSubGridVisible(true);
     customPlot->yAxis->grid()->setSubGridVisible(true);
     customPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
     customPlot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
     customPlot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
     customPlot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(30, 30, 30));
    plotGradient.setColorAt(1, QColor(10, 10, 10));
     customPlot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
     customPlot->axisRect()->setBackground(axisRectGradient);

    customPlot->repaint();
}

void MainWindow::on_pushButton_clicked()
{
   ui->widget->clearGraphs();
   dataTimer.start(40);
   Run(ui->widget);
   Runcam();

}


void MainWindow::Runcam(){

    camera.open(1);

}

void MainWindow::Run(QCustomPlot *customPlot){

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%s");
    customPlot->xAxis->setTicker(timeTicker);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->yAxis->setRange(0, 1.2);

}


void MainWindow::pushNew()
{
  static QTime time(QTime::currentTime());
  double key = time.elapsed()/1000.0;
  QElapsedTimer timer;

  ui->widget->graph(0)->addData(key, pulse);
  ui->widget->graph(0)->rescaleValueAxis();
  ui->widget->xAxis->setRange(key, 8, Qt::AlignRight);
  ui->widget->replot();

  }


void MainWindow::newNumberCame(double num){
    pulse = num;
    //pushNew();
    calc.addNewData(num);
    qDebug()<<"image proccessing ellapsed "<<ellapser.elapsed();
}


void MainWindow::calc_started(){
    dataTimer.stop();

}

void MainWindow::collect_started(){
    camera.release();
    dataTimer.stop();
    ui->widget_2->xAxis->setRange(0,5);
    ui->widget_2->yAxis->setRange(0,10000000);
    bars1->setWidth(9/(double)calc.FftresultX.size());
    bars1->setData(calc.FftresultX,calc.FftresultY);
    ui->widget_2->replot();
    calc.clerContainers();
    //dataTimer.start(50);
}

void MainWindow::showHeartRate(double heartRate) {

    pulse_norm = heartRate;
    ui->lcdNumber->display(pulse_norm);

}

void MainWindow::pasteim(){


    cv::Mat image;


   if (! camera.read(image)) {
       dataTimer.stop();
       QMessageBox::information(
               this,
               tr("Warning"),
               tr("Camera error occured") );
       return;
   }


    ellapser.start();
    my.fullOneFrameProcess(image);

    QImage im = putImage(image);
    ui->label_2->setGeometry(5,5,(im.width()/14)*10,(im.height()/14)*10);
    ui->label_2->setScaledContents(true);
    QPixmap Picture_to_show((im.width()/14)*10,(im.height()/14)*10);
    QPainter painter(&Picture_to_show);

    if (!my.isface){
       painter.drawPixmap(0,0,QPixmap::fromImage(im.scaledToHeight((im.height()/14)*10)));
       painter.drawPixmap((ui->label_2->width()/2)-(im.height()/25)*5,
                           (ui->label_2->height()/2-(im.height()/25)*5),
                           QPixmap::fromImage(face.scaledToHeight((im.height()/25)*10)));

    } else {
        count_of_frames_processed+=1;
        cv::Point center( my.face_x + my.face_r*0.5, my.face_y + my.face_r*0.5 );
        ellipse(image, center, cv::Size( my.face_r*0.5, my.face_r*0.5),
                270, 0, (ONE_POINT_OF_DROWING)*(count_of_frames_processed%FRAMES),
                cv::Scalar( 0, 153, 255 ), 4, 8, 0 );
        im = putImage(image);
        painter.drawPixmap(0,0,QPixmap::fromImage(im.scaledToHeight((im.height()/14)*10)));


    }
    ui->label_2->setPixmap(Picture_to_show);

    //camera.release();



}


void MainWindow::on_pushButton_2_clicked() {
    camera.release();
    dataTimer.stop();

}


QImage MainWindow::putImage(const cv::Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS=1
    if(mat.type()==CV_8UC1)
    {
        // Set the color table (used to translate colour indexes to qRgb values)
        QVector<QRgb> colorTable;
        for (int i=0; i<256; i++)
            colorTable.push_back(qRgb(i,i,i));
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
        img.setColorTable(colorTable);
        return img;
    }
    // 8-bits unsigned, NO. OF CHANNELS=3
    if(mat.type()==CV_8UC3)
    {
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}


void MainWindow::savePdfReport() {
    saver a;
    if(!a.setDir(QFileDialog::getSaveFileName(this, tr("Save File"),
                                          "./untitled.pdf",
                                          tr("PDF document (*.pdf)")))){

        a.setText(QString::number(pulse_norm));
        QPixmap image;
        QPixmap image2;
        image = ui->widget->toPixmap();
        image2 = ui->widget_2->toPixmap();
        a.setIm(&(image), &(image2));
        a.save();

    }
}


void MainWindow::on_pushButton_3_clicked() {
    savePdfReport();
}
