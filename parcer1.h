#ifndef PARCER1_H
#define PARCER1_H

#include <QObject>

class parcer1 : public QObject
{
    Q_OBJECT
public:
    explicit parcer1(QObject *parent = 0);

signals:
    void abcCame(int a);

public slots:
};

#endif // PARCER1_H
