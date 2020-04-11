#ifndef MYCLASS_H
#define MYCLASS_H

#include<QtWidgets>
#include <QObject>

class MyClass: public QObject{
    Q_OBJECT
public:
    MyClass();
public slots:
    void changeText(const QString&);
private:
    QLabel lbl;
};

#endif
