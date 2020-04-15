#include "box.h"

Box::Box(QWidget *parent): QWidget(parent), sendButton(new QPushButton("send")), textBox(new QTextEdit), textLine(new QLineEdit), layout(new QVBoxLayout){
    textBox->setReadOnly(1);
    layout->addWidget(textBox);
    layout->addWidget(textLine);
    layout->addWidget(sendButton);
    this->resize(800, 800);
    this->setLayout(layout);

    QObject::connect(sendButton, SIGNAL(clicked()), this, SLOT(sendData()));
}

void Box::displayText(QString &message){
    textBox->insertPlainText(">>\t");
    textBox->insertPlainText(message);
    textBox->insertPlainText("\n");
}

void Box::sendData(){
    QString message = textLine->text();
    textLine->clear();
    textBox->insertPlainText("You:\t");
    textBox->insertPlainText(message);
    textBox->insertPlainText("\n");
    emit sendText(message);
}
