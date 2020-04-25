#include "client.h"

Client::Client(QString host, quint16 Port, QWidget *pwgt):QWidget(pwgt){
    QLabel *lblTitle = new QLabel("CLIENT");
    consoleOutput = new QTextEdit;
    consoleOutput->setReadOnly(true);
    lblClientState = new QLabel();
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(lblTitle);
    layout->addWidget(consoleOutput);
    layout->addWidget(lblClientState);
    setLayout(layout);
    setWindowTitle("Client");
    this->resize(500, 500);

    time = new QTime;

    socket = new QTcpSocket(this);
    socket->connectToHost(host, Port, QIODevice::ReadOnly, QAbstractSocket::IPv4Protocol);

    connect(socket, &QAbstractSocket::connected, [this, host](){
        consoleOutput->append(time->currentTime().toString("hh:mm:ss.zzz") + "|INFO|Connection to server success. Server IP address: " + host);
    });
    connect(socket, SIGNAL(readyRead()), SLOT(slotReadData()));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(slotClientState(QAbstractSocket::SocketState)));
}

void Client::slotReadData(){
    QByteArray data;
    QDataStream streamDataIn(socket);
    streamDataIn.setVersion(QDataStream::Qt_5_14);
    streamDataIn >> data;
    consoleOutput->append(time->currentTime().toString("hh:mm:ss.zzz") + "|DATA|Context from server:\n\t" + data);
}

void Client::slotClientState(QAbstractSocket::SocketState state){
    switch (state) {
    case 0:
        lblClientState->setText("Unconnected state.");
    case 1:
        lblClientState->setText("Server lookup state...");
    case 2:
        lblClientState->setText("Connecting state...");
    case 3:
        lblClientState->setText("Connected state.");
    case 6:
        lblClientState->setText("Closing state.");
    }
}
