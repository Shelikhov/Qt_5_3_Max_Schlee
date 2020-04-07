#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>

class Counter: public QObject{
    Q_OBJECT
public:
    Counter();
private:
    int number;
signals:
    void exit();
    void showNumber(int);
public slots:
    void slotInc();
};

#endif
