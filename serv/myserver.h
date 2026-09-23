#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
class MyServer:public QObject
{
    Q_OBJECT
public:
    MyServer();
    Q_INVOKABLE bool start(unsigned port);
    bool is_work();
private:
    QTcpServer* m_tcpServer=new QTcpServer;
    QVector<QTcpSocket*> m_hosts;
private slots:
    void connected();
    void read();
    void disconnected();//имена connect disconnect заняты в ку обжекте, может стоило ко всем функциям добавлять my_ или что то такое
};

#endif // MYSERVER_H
