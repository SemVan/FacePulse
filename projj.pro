#-------------------------------------------------
#
# Project created by QtCreator 2017-04-22T20:36:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = projj
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    saver.cpp \
    logger.cpp \
    qcustomplot.cpp \
    imageprocessor.cpp \
    keepncalc.cpp

HEADERS  += mainwindow.h \
    saver.h \
    logger.h \
    qcustomplot.h \
    imageprocessor.h \
    fir_tuk74.h \
    keepncalc.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS +=-O2 -std=c++11 -Wall -Wextra \


DISTFILES += \
    1.png

    INCLUDEPATH += C:\opencvmingw\install\include\


    LIBS +=C:\opencvmingw\install\x86\mingw\bin\libopencv_core310.dll
    LIBS +=C:\opencvmingw\install\x86\mingw\bin\libopencv_highgui310.dll
    LIBS +=C:\opencvmingw\install\x86\mingw\bin\libopencv_imgcodecs310.dll
    LIBS +=C:\opencvmingw\install\x86\mingw\bin\libopencv_videoio310.dll
    LIBS +=C:\opencvmingw\install\x86\mingw\bin\libopencv_imgproc310.dll
    LIBS +=C:\opencvmingw\install\x86\mingw\bin\libopencv_objdetect310.dll

    LIBS +=C:\opencvmingw\install\x86\mingw\lib\libopencv_core310.dll.a
    LIBS +=C:\opencvmingw\install\x86\mingw\lib\libopencv_highgui310.dll.a
    LIBS +=C:\opencvmingw\install\x86\mingw\lib\libopencv_imgcodecs310.dll.a
    LIBS +=C:\opencvmingw\install\x86\mingw\lib\libopencv_videoio310.dll.a
    LIBS +=C:\opencvmingw\install\x86\mingw\lib\libopencv_imgproc310.dll.a
    LIBS +=C:\opencvmingw\install\x86\mingw\lib\libopencv_objdetect310.dll.a

INCLUDEPATH += C:/Coding/fftw/

LIBS +=  C:/Coding/fftw/libfftw3-3.dll
