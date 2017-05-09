#ifndef KEEPNCALC_H
#define KEEPNCALC_H

#include <QVector>
#include <QObject>
#include <fftw3.h>
#include <QElapsedTimer>


class KeepNcalc : public QObject
{
    Q_OBJECT

public:
    explicit KeepNcalc(QObject *parent = 0);
    void addNewData(double green);
    void clerContainers();
    QVector<double> FftresultY;
    QVector<double> FftresultX;

private:
    const int vectorSize=512;
    QElapsedTimer timer;

    void fullSignalProcess();

    QVector<double> greenChannel;

    int numberOfElements;

    QVector<double> filterIt(QVector<double> toFilt);
    QVector<double> straightIt(QVector<double> toStraight);
    QVector<double> averFilt(QVector<double> toFilt,int order);


    double findHeartRate();
    void calculateFft(int n,QVector<double> toCalc);


signals:
    void calculating();
    void data_collect();
    void rateIsReady(double heartRate);
public slots:
};

#endif // KEEPNCALC_H
