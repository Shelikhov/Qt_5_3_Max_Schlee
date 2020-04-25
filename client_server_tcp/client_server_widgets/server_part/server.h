#ifndef SERVER_H
#define SERVER_H

#include <QtWidgets>
#include<QtNetwork>

class Server: public QWidget{
    Q_OBJECT
public:
    Server(quint16, QWidget *pwgt = 0);
private:
    quint16 Port;
    QTextEdit *consoleOutput;
    QDateTime *time;
    QTcpServer *serverSocket;
public slots:
    void slotNewConnection();
};

#endif


