//#include "mainwindow.h"

#include"counter.h"
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QLabel lbl("0");
    Counter cntr;//object for increasing value into the lbl
    QPushButton but("Add number");//button for increasing

    lbl.show();
    but.show();//

    QObject::connect(&but, SIGNAL(clicked()), &cntr, SLOT(slotInc()));//to click button
    QObject::connect(&cntr, SIGNAL(showNumber(int)), &lbl, SLOT(setNum(int)));//to show result in window lbl
    QObject::connect(&cntr, SIGNAL(exit()), &app, SLOT(quit()));//to exit from app
    return app.exec();
}
