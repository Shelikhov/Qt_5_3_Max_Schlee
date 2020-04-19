#include "shell.h"

Shell::Shell(QWidget *pwgt): QWidget(pwgt){
    pProc = new QProcess(this);
    pTextEdit = new QTextEdit;
    pCommandLine = new QLineEdit("");
    pLbl = new QLabel("Command");

    QPushButton *pButton = new QPushButton("Enter");

    QHBoxLayout *pHorLayout = new QHBoxLayout;
    pHorLayout->addWidget(pLbl);
    pHorLayout->addWidget(pCommandLine);
    pHorLayout->addWidget(pButton);

    QVBoxLayout *pVerLayout = new QVBoxLayout;
    pVerLayout->addWidget(pTextEdit);
    pVerLayout->addLayout(pHorLayout);

    setLayout(pVerLayout);

    connect(pProc, SIGNAL(readyReadStandartOutput()), SLOT(slotDataOnStdout()));
    connect(pButton, SIGNAL(clicked()), SLOT(slotReturnPressed()));
    connect(pCommandLine, SIGNAL(returnPressed()), SLOT(slotReturnPressed()));
}

void Shell::slotReturnPressed(){
    QString str = "";
//#ifdef Q_WS_WIN
  //  str = "cmd /C ";
//#endif
    str += pCommandLine->text();
    pProc->start(str);
    pCommandLine->clear();
}

void Shell::slotDataOnStdout(){
    QString outData = pProc->readAllStandardOutput();
    pTextEdit->append(outData);
}
