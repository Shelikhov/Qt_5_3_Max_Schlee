#include "timer.h"

Timer::Timer(QObject *obj): QObject(obj), value(10){
    connect(&myTimer, SIGNAL(timeout()), SLOT(slotChangeVal()));
}

void Timer::slotChangeVal(){
    emit changeValue(--value);
    if(!value)
        emit toFinish();
}

void Timer::startTimer(){
    myTimer.start(1000);
}
