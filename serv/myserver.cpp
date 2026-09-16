#include "myserver.h"
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
    QTcpSocket *host= tcpServer->nextPendingConnection();
    hosts.append(host);
    connect(host,&QTcpSocket::readyRead,this,[this, host]() {read(host);});
    connect(host,&QTcpSocket::disconnected,this,[this, host]() {disconnected(host);});
    //host->readyRead();
    qDebug()<<"host connected "<<host->peerAddress().toString()<<Qt::endl;
    qDebug()<<"host name "<<host->peerName()<<Qt::endl;

    host->write("Darova!");
}
void MyServer::read(QTcpSocket* sender){
    QByteArray data = sender->readAll();
    qDebug() << "Server received:" << QString::fromUtf8(data);
    for (QTcpSocket *host : hosts){
        if(host!=sender){
            host->write(data);
        }
    }
}
void MyServer::disconnected(QTcpSocket* sender){
    hosts.removeOne(sender);//возвращает тру если удалил успешно
    sender->deleteLater();
    /*
    for (size_t i=0;i<hosts.size();i++){
        if(hosts[i]==sender){
            hosts.removeAt(i);
            break;
        }
    }
    */
}
