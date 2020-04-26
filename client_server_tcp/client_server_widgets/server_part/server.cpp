#include "server.h"

Server::Server(QWidget *pwgt)
    :QWidget(pwgt),
    console(new QTextEdit),
    time(new QDateTime),
    serverSocket(new QTcpServer(this)){

    console->setReadOnly(true);

    QLabel *windowTitle = new QLabel("SERVER");
    QPushButton *buttPort = new QPushButton("port");
    QVBoxLayout *layoutVer = new QVBoxLayout;
    QHBoxLayout *layoutHor = new QHBoxLayout;
    layoutHor->addWidget(windowTitle);
    layoutHor->addWidget(buttPort);
    layoutVer->addLayout(layoutHor);
    layoutVer->addWidget(console);
    setLayout(layoutVer);
    this->resize(800, 500);

    serverSocket->listen(QHostAddress::Any, port);
    if(!serverSocket->isListening()){
        consoleOutput("To bind address and port to the server socket.", 0);
        serverSocket->close();
        return;
    }
    else
        consoleOutput("To bind address and port to the server socket.<SUCCESS>", 1);

    connect(serverSocket, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
    connect(buttPort, SIGNAL(clicked()), this, SLOT(slotSetPort()));
}

void Server::slotNewConnection(){//To create client socket during new connection.
    QTcpSocket *clientSocket = serverSocket->nextPendingConnection();
    if(clientSocket->state() != QAbstractSocket::ConnectedState)
        consoleOutput("New connection. IP address: " + clientSocket->peerAddress().toString(), 0);
    else
        consoleOutput("New connection. IP address: " + clientSocket->peerAddress().toString() + "<SUCCESS>", 1);

    QTimer *timer = new QTimer;//Through every 3 seconds to send text to client
    timer->start(3000);

//    connect(timer, &QTimer::timeout, [clientSocket](){
        QByteArray data;
        QDataStream dataOut(&data, QIODevice::ReadWrite);
        dataOut.setVersion(QDataStream::Qt_5_14);
        dataOut << "Test message from server!!!";
        clientSocket->write(data);//});

    connect(clientSocket, &QTcpSocket::disconnected, [clientSocket, this](){
        clientSocket->deleteLater();
        if(clientSocket->state() != QAbstractSocket::UnconnectedState){
            consoleOutput("Disconnection. IP address: " + clientSocket->peerAddress().toString(), 0);
            clientSocket->close();
        }else{
            consoleOutput("Disconnection. IP address: " + clientSocket->peerAddress().toString() + "<SUCCESS>", 1);
            clientSocket->close();
        }});
    connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(slotClientState(QAbstractSocket::SocketState)));
}

void Server::slotClientState(QAbstractSocket::SocketState state){
    switch (state) {
    case 0:
        consoleOutput("Socket state: unconnected.", 2);
    case 1:
        consoleOutput("Socket state: server lookup...", 1);
    case 2:
        consoleOutput("Socket state: connecting to server...", 1);
    case 3:
        consoleOutput("Socket state: connected.", 1);
    case 6:
        consoleOutput("Socket state: socket closed.", 2);
    }
}

void Server::consoleOutput(QString message, qint16 status){
    QString state;
    switch (status) {
    case 0:
        state = "ERROR";
    case 1:
        state = "INFO";
    case 2:
        state = "WARN";
    default:
        state = "UNDEF";
    }
    message = time->currentDateTime().toString("hh:mm:ss.zzz") + "|" + state + "|" + message;
    console->append(message);
}

void Server::slotSetPort(){
    QWidget *windowPort = new QWidget(this, Qt::Window);
    QLineEdit *linePort = new QLineEdit;
    QLabel *lblPort = new QLabel("Port:");
    QPushButton *buttOK = new QPushButton("Ok");
    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(lblPort);
    layout->addWidget(linePort);
    layout->addWidget(buttOK);
    windowPort->setLayout(layout);
    windowPort->resize(150, 150);
    windowPort->show();

    connect(buttOK, &QPushButton::clicked, [this, linePort, windowPort](){
        port = linePort->text().toInt();
        windowPort->close();
    });
}
