//#include"myclass.h"
#include <QtWidgets>
#include"box.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    Box bx1, bx2;
    bx1.move(50, 50);
    bx1.show();
    bx2.move(950, 50);
    bx2.show();

    QObject::connect(&bx1, SIGNAL(sendText(QString&)), &bx2, SLOT(displayText(QString&)));
    QObject::connect(&bx2, SIGNAL(sendText(QString&)), &bx1, SLOT(displayText(QString&)));

    return app.exec();
}
