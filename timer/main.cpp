//#include"myclass.h"
#include <QtWidgets>
#include"timer.h"
#include"mythread.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    //To create electronic indicator.
    QLCDNumber *lcdNum = new QLCDNumber;
    lcdNum->setSegmentStyle(QLCDNumber::Filled);
    lcdNum->display(10);
    lcdNum->resize(350, 110);
    lcdNum->show();

    //Order is important.
    Timer tmr;
    MyThread thread;
    tmr.moveToThread(&thread);
    thread.start();
    tmr.startTimer();

    QObject::connect(&tmr, SIGNAL(changeValue(int)), lcdNum, SLOT(display(int)));
    QObject::connect(&tmr, SIGNAL(toFinish()), &app, SLOT(quit()));

    return app.exec();
}
