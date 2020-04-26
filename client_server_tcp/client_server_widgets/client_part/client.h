#ifndef CLIENT_H
#define CLIENT_H

#include <QtWidgets>
#include<QtNetwork>

class Client: public QWidget{
    Q_OBJECT
public:
    Client(QWidget *pwgt = 0);
    QHostAddress serverAddress;
    qint16 port;
    void consoleOutput(QString, qint16);
private:
    QTcpSocket *socket;
    QTextEdit *console;
    QLabel *lblClientState;
    QTime *time;
public slots:
    void slotReadData();//To write data from socket to consoleOut.
    void slotClientState(QAbstractSocket::SocketState);//To display state of client connection with server.
    void slotSetServerParametrs();//To set server host name and port.
    void slotOutputError(QAbstractSocket::SocketError);//To output errors occured with the socket to client console.
};

#endif
