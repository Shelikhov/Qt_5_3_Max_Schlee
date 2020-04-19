#ifndef SHELL_H
#define SHELL_H

#include <QtWidgets>
#include<QProcess>

class Shell: public QWidget{
    Q_OBJECT
public:
    Shell(QWidget *pwgt = 0);
private:
    QProcess *pProc;
    QLineEdit *pCommandLine;
    QTextEdit *pTextEdit;
    QLabel *pLbl;
public slots:
    void slotReturnPressed();
    void slotDataOnStdout();
};

#endif
