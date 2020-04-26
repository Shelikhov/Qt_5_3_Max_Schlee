#ifndef SERVER_H
#define SERVER_H

#include <QtWidgets>
#include<QtNetwork>

class Server: public QWidget{
    Q_OBJECT
public:
    Server(quint16, QWidget *pwgt = nullptr);
    void consoleOutput(QString, qint16);
private:
    quint16 Port;
    QTextEdit *console;
    QDateTime *time;
    QTcpServer *serverSocket;
public slots:
    void slotNewConnection();
    void slotClientState(QAbstractSocket::SocketState);
};

#endif


