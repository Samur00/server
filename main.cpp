#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "serv/myserver.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    MyServer *server=new MyServer;
    server->start(11111);

    return QGuiApplication::exec();
/*
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("server", "Main");
*/

}
