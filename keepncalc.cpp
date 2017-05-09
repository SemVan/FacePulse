#include "keepncalc.h"
#include <QObject>
#include <fftw3.h>
#include <math.h>
#include <fir_tuk74.h>
#include "iostream"
#include "qdebug.h"

#define     PI_POP 1.57
#define     SECONDS 60

KeepNcalc::KeepNcalc(QObject *parent) : QObject(parent)
{
    greenChannel.clear();
    numberOfElements=0;

}

void KeepNcalc::fullSignalProcess() {
    QVector<double> SignalFiletered=filterIt(greenChannel);
    calculateFft(vectorSize,SignalFiletered);
    rateIsReady(findHeartRate());
    data_collect();
}

void KeepNcalc::addNewData(double green) {
    qDebug()<<"taking pic took "<<timer.elapsed();
    timer.start();
    greenChannel.append(green);
    numberOfElements++;
    //std::cout<<numberOfElements<< "num"<<std::endl;
    if (numberOfElements==vectorSize+BL_equ) {
        calculating();
        timer.start();
        fullSignalProcess();
        greenChannel.remove(0);
        numberOfElements--;
        qDebug()<<"math took"<<timer.elapsed();
    }
}


QVector<double> KeepNcalc::averFilt(QVector<double> toFilt, int order) {
    QVector<double> filtered;



    for (int i=order/2+1;i<toFilt.size()-order/2;i++) {

        double aver=0;
        for (int j=i-order/2; j<i+order/2; j++) {
            aver+=toFilt.at(j);
        }
        aver=aver/order;
        filtered.append(aver);

    }


    return filtered;
}

QVector<double> KeepNcalc::filterIt(QVector<double> toFilt) {

    int num=0;
    int B_filter_len_div2=BL_equ/2;

    QVector<double> filtered;


    for (int i = B_filter_len_div2; i<toFilt.size() - B_filter_len_div2;  i++) {

            double filt=0;

            for (int j=0;j<BL_equ;j++) {
                filt += toFilt.at(i-B_filter_len_div2+j) * B_equ[j];
            }

            filtered.append(filt);
            num++;
    }


    return filtered;
}



double KeepNcalc::findHeartRate() {

    double max = 0;
    double maxCoord = 0;
    for (int i=1;   i < FftresultX.size()-1;   i++) {
        if ((FftresultX.at(i) < 4) &&
                (FftresultX.at(i) >1) &&
                (FftresultY.at(i) > max) ) {
            maxCoord=FftresultX.at(i);
            max=FftresultY.at(i);
        }
    }

    qDebug()<<"freq="<<maxCoord;
    return maxCoord* SECONDS / PI_POP;
}


QVector<double> KeepNcalc::straightIt(QVector<double> toStraight) {
    double aver=0;
    QVector<double> straighted;
    for (int i = 0; i < toStraight.size() - 10; i++) {
        aver=0;
        for (int j = 0; j < 10; j++) {
            aver += toStraight.at(j+i);
        }
        aver = aver/10;
        straighted.append(toStraight.at(i)-aver);
    }
    for (int i = toStraight.size()-10;i < toStraight.size(); i++) {
        straighted.append(toStraight.at(i)-aver);
    }

    return straighted;
}


void KeepNcalc::calculateFft(int n,QVector<double> toCalc) {
    int n_pop = n/2;

    fftw_complex out[n];
    double in[n];
    fftw_plan p;


    for(int i=0; i<n; i++) {
        in[i] = toCalc.at(i);

    }


    p = fftw_plan_dft_r2c_1d(n, in, out, FFTW_ESTIMATE);
    fftw_execute(p);

    FftresultY.clear();
    FftresultX.clear();

    for(int i=0; i < n_pop;i++) {
        double real = out[i][0];
        real = real*real;
        double imaginary = out[i][1];
        imaginary = imaginary * imaginary;
        FftresultY.append(sqrt(real + imaginary));

        FftresultX.append((i * (1 / (n * 40 * 0.001))));
    }


}


void KeepNcalc::clerContainers() {

    FftresultY.clear();
    FftresultX.clear();

}
