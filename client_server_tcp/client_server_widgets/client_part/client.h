#ifndef CLIENT_H
#define CLIENT_H

#include <QtWidgets>
#include<QtNetwork>

class Client: public QWidget{
    Q_OBJECT
public:
    Client(QString, quint16, QWidget *pwgt = 0);
private:
    QTcpSocket *socket;
    QTextEdit *consoleOutput;
    QLabel *lblClientState;
    QTime *time;
public slots:
    void slotReadData();
    void slotClientState(QAbstractSocket::SocketState);
};

#endif
