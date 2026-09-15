#include "myserver.h"
#include <QTcpSocket>
MyServer::MyServer(){
    connect(tcpServer, &QTcpServer::newConnection, this, &MyServer::connected);
}
bool MyServer::start(unsigned port){
    if(tcpServer->isListening()){
        return false;
    }
    return tcpServer->listen(QHostAddress::Any,port);
}
bool MyServer::is_work(){
    return tcpServer->isListening();
}
void MyServer::connected(){
    QTcpSocket *client = tcpServer->nextPendingConnection();
    qDebug()<<"host connected "<<client->peerAddress().toString()<<Qt::endl;
    qDebug()<<"host name "<<client->peerName()<<Qt::endl;

    client->write("Hello!");
}