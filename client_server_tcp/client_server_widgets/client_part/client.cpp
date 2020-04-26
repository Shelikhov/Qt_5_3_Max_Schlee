#include "client.h"

Client::Client(QWidget *pwgt)
    :QWidget(pwgt),
      socket(new QTcpSocket(this)),
      console(new QTextEdit),
      lblClientState(new QLabel),
      time(new QTime){

    QLabel *lblTitle = new QLabel("CLIENT");
    QPushButton *buttServer = new QPushButton("Server"), *buttConnect = new QPushButton("Connect"), *buttDisconnect = new QPushButton("Disconnect");
    console->setReadOnly(true);
    QHBoxLayout *layoutHor = new QHBoxLayout;
    layoutHor->addWidget(lblTitle);
    layoutHor->addWidget(buttServer);
    QVBoxLayout *layoutVer = new QVBoxLayout;
    layoutVer->addLayout(layoutHor);
    layoutVer->addWidget(console);
    layoutVer->addWidget(lblClientState);
    layoutVer->addWidget(buttConnect);
    layoutVer->addWidget(buttDisconnect);
    setLayout(layoutVer);
    setWindowTitle("Client");
    this->resize(500, 500);

    connect(socket, &QAbstractSocket::connected, [this](){
        consoleOutput("Connection to server success. Server IP address: " + serverAddress.toString(), 1);
    });
    connect(socket, SIGNAL(readyRead()), SLOT(slotReadData()));
    connect(buttServer, SIGNAL(clicked()), SLOT(slotSetServerParametrs()));
    connect(buttDisconnect, &QAbstractButton::clicked, socket, &QAbstractSocket::disconnectFromHost);
    connect(buttConnect, &QPushButton::clicked, [this](){
        socket->connectToHost(serverAddress, port, QIODevice::ReadWrite);
    });
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(slotClientState(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError )), this, SLOT(slotOutputError(QAbstractSocket::SocketError)));
}

void Client::slotReadData(){
    QByteArray data;
    QDataStream streamDataIn(socket);
    streamDataIn.setVersion(QDataStream::Qt_5_14);
    streamDataIn >> data;
    consoleOutput("Context from server:\n\t" + data, 1);
}

void Client::slotClientState(QAbstractSocket::SocketState state){
    switch (state) {
    case 0:
        lblClientState->setText("Unconnected state.");
        consoleOutput("Socket state: unconnected.", 2);
        break;
    case 1:
        lblClientState->setText("Server lookup state...");
        consoleOutput("Socket state: server lookup...", 1);
        break;
    case 2:
        lblClientState->setText("Connecting state...");
        consoleOutput("Socket state: connecting to server...", 1);
        break;
    case 3:
        lblClientState->setText("Connected state.");
        consoleOutput("Socket state: connected.", 1);
        break;
    case 6:
        lblClientState->setText("Closing state.");
        consoleOutput("Socket state: socket closed.", 2);
        break;
    default:
        lblClientState->setText("Undefined state.");
        consoleOutput("Socket state: undefined.", 3);
    }
}

void Client::slotSetServerParametrs(){
    QWidget *windowConnect = new QWidget(this, Qt::Window);
    QLineEdit *lineIP = new QLineEdit, *linePort = new QLineEdit;
    QLabel *lblIP = new QLabel("IP:"), *lblPort = new QLabel("Port:");
    QPushButton *buttOK = new QPushButton("Ok");
    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(lblIP);
    layout->addWidget(lineIP);
    layout->addWidget(lblPort);
    layout->addWidget(linePort);
    layout->addWidget(buttOK);
    windowConnect->setLayout(layout);
    windowConnect->resize(150, 150);
    windowConnect->show();

    connect(buttOK, &QPushButton::clicked, [this, lineIP, linePort, windowConnect](){
        serverAddress.setAddress(lineIP->text());
        port = linePort->text().toInt();
        windowConnect->close();
    });
}

void Client::consoleOutput(QString message, qint16 status){
    QString state;
    switch (status) {
    case 0:
        state = "ERROR";
        break;
    case 1:
        state = "INFO";
        break;
    case 2:
        state = "WARN";
        break;
    default:
        state = "UNDEF";
    }
    message = time->currentTime().toString("hh:mm:ss.zzz") + "|" + state + "|" + message;
    console->append(message);
}

void Client::slotOutputError(QAbstractSocket::SocketError error){
    switch (error) {
    case QAbstractSocket::HostNotFoundError:
        consoleOutput("Host not found. Check the host name and port settings.", 0);
        break;
    case QAbstractSocket::SocketTimeoutError:
        consoleOutput("The operation timed out.", 0);
        break;
    case QAbstractSocket::NetworkError:
        consoleOutput("Problem with network (for example cable plugged out).", 0);
        break;
    case QAbstractSocket::SocketAddressNotAvailableError:
        consoleOutput("Host name unavailable.", 0);
        break;
    default:
        consoleOutput(tr("Cause: %1.").arg(socket->errorString()), 0);
    }
}
