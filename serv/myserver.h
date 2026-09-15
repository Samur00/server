#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
class MyServer:public QObject
{
    Q_OBJECT
public:
    MyServer();
    Q_INVOKABLE bool start(unsigned port);
    bool is_work();
private:
    QTcpServer* tcpServer=new QTcpServer;
private slots:
    void connected();
};

#endif // MYSERVER_H
