#include "myserver.h"
MyServer::MyServer(){
    connect(m_tcpServer, &QTcpServer::newConnection, this, &MyServer::connected);
}
bool MyServer::start(unsigned port){
    if(m_tcpServer->isListening()){
        return false;
    }
    return m_tcpServer->listen(QHostAddress::Any,port);
}
bool MyServer::is_work(){
    return m_tcpServer->isListening();
}
void MyServer::connected(){
    QTcpSocket *host= m_tcpServer->nextPendingConnection();
    m_hosts.append(host);
    connect(host,&QTcpSocket::readyRead,this,&MyServer::read);
    connect(host,&QTcpSocket::disconnected,this,&MyServer::disconnected);
    //host->readyRead();
    qDebug()<<"host connected "<<host->peerAddress().toString();
    qDebug()<<"host name "<<host->peerName();

    host->write("Darova!");
}
void MyServer::read(){

    //this->sender();
    auto *clientSocket= qobject_cast<QTcpSocket*>(sender());
    if(!clientSocket){
        return;
    }
    QByteArray data = clientSocket->readAll();
    qDebug() << "Server received:" << QString::fromUtf8(data);
    for (QTcpSocket *host : m_hosts){
        if(host!=clientSocket){
            host->write(data);
        }
    }
}
void MyServer::disconnected(){
    auto *clientSocket= qobject_cast<QTcpSocket*>(sender());
    if(!clientSocket){
        return;
    }
    m_hosts.removeOne(clientSocket);//возвращает тру если удалил успешно
    clientSocket->deleteLater();
}
