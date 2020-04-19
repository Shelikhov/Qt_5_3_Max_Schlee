#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include<QTimer>

class Timer: public QObject{
    Q_OBJECT
private:
    int value;//For display on the electronic indicator.
    QTimer myTimer;
public:
    Timer(QObject *obj = 0);
    void startTimer();//To launch timer.
signals:
    void changeValue(int);
    void toFinish();//To finish programm.
public slots:
    void slotChangeVal();
};

#endif
