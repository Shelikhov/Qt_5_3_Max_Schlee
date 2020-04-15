#ifndef BOX_H
#define BOX_H

#include <QtWidgets>

class Box: public QWidget{
    Q_OBJECT
public:
    Box(QWidget *parent = nullptr);
    QPushButton *sendButton;
public slots:
    void displayText(QString &);
    void sendData();
signals:
    void sendText(QString &);
private:
    QTextEdit *textBox;
    QLineEdit *textLine;
    QVBoxLayout *layout;
};

#endif
