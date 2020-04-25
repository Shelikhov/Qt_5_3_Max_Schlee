#include "server.h"

Server::Server(quint16 portNumber, QWidget *pwgt):QWidget(pwgt), Port(portNumber){

    consoleOutput = new QTextEdit;
    consoleOutput->setReadOnly(true);

    time = new QDateTime();

    QLabel *windowTitle = new QLabel("SERVER");
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(windowTitle);
    layout->addWidget(consoleOutput);
    setLayout(layout);
    this->resize(800, 500);

    serverSocket = new QTcpServer();//To create server socket.
    serverSocket->listen(QHostAddress::LocalHost, Port);
    if(!serverSocket->isListening())
        consoleOutput->append((time->currentDateTime()).toString("hh:mm:ss.zzz") + "|ERROR|To bind address and port to the server socket.");
    else
        consoleOutput->append((time->currentDateTime()).toString("hh:mm:ss.zzz") + "|INFO|To bind address and port to the server socket.<SUCCESS>");

    connect(serverSocket, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
}

void Server::slotNewConnection(){//To create client socket during new connection.
    QTcpSocket *clientSocket = serverSocket->nextPendingConnection();
    if(clientSocket->state() != QAbstractSocket::ConnectedState)
        consoleOutput->append((time->currentDateTime()).toString("hh:mm:ss.zzz") + "|ERROR|New connection. IP address: " + (clientSocket->peerAddress()).toString());
    else
        consoleOutput->append((time->currentDateTime()).toString("hh:mm:ss.zzz") + "|INFO|New connection. IP address: " + (clientSocket->peerAddress()).toString() + "<SUCCESS>");

    QTimer *timer = new QTimer;//Through every 3 seconds to send text to client
    timer->start(3000);

    connect(timer, &QTimer::timeout, [clientSocket](){
        QByteArray data;
        QDataStream dataOut(&data, QIODevice::ReadWrite);
        dataOut.setVersion(QDataStream::Qt_5_14);
        dataOut << "test route";
        clientSocket->write(data);});
    connect(clientSocket, &QTcpSocket::disconnected, [clientSocket, this](){
        clientSocket->deleteLater();
        if(clientSocket->state() != QAbstractSocket::UnconnectedState){
            consoleOutput->append((time->currentDateTime()).toString("hh:mm:ss.zzz") + "|ERROR|Disconnection. IP address: " + (clientSocket->peerAddress()).toString());
            clientSocket->close();
        }else{
            consoleOutput->append((time->currentDateTime()).toString("hh:mm:ss.zzz") + "|INFO|Disconnection success. IP address: " + (clientSocket->peerAddress()).toString());
            clientSocket->close();
        }});
}
