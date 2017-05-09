#include "saver.h"
#include "ctime"
#include <QTextDocument>
#include "QTextCursor"
#include <QPrinter>
#include <QApplication>

saver::saver(QObject *parent) : QObject(parent)
{

}

bool saver::setDir(QString dir){
    if (dir.length()==0){
        return 1;
    }
    this->dir=dir;
    return 0;

}
void saver::setIm(QPixmap *im,QPixmap *im2){
    this->image = im;
    this->image2 = im2;
}

void saver::setText(QString text){
    this->text = "<p>Дата: ";
    std::time_t result = std::time(0);
    this ->text +=QString::fromStdString(std::asctime(std::localtime(&result)))+"<\p>";
    this ->text +="<p>Пульс = "+text+"<\p>";


}
void saver::save(){
    QTextDocument doc;
    doc.setHtml( text );
    QPrinter printer;
    printer.setOutputFileName(dir);
    printer.setOutputFormat(QPrinter::PdfFormat);
    QTextCursor cursor(&doc);
    QImage img = (*image).toImage();
    cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
    cursor.insertImage(img);

    img = (*image2).toImage();
    cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
    cursor.insertImage(img);
   // doc.loadResource(QPixmap, image);
    doc.print(&printer);

    printer.newPage();
}
