#include"myclass.h"
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MyClass obj;

    QPushButton but1("button 1");
    but1.show();

    QPushButton but2("button 2");
    but2.show();

    QSignalMapper mapObj;

    QObject::connect(&but1, SIGNAL(clicked()), &mapObj, SLOT(map()));
    mapObj.setMapping(&but1, "Action from button 1");

    QObject::connect(&but2, SIGNAL(clicked()), &mapObj, SLOT(map()));
    mapObj.setMapping(&but2, "Action from button 2");

    QObject::connect(&mapObj, SIGNAL(mapped(const QString&)), &obj, SLOT(changeText(const QString&)));
    return app.exec();
}
