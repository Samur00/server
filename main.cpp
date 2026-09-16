#include "serv/myserver.h"
#include <qcoreapplication.h>
int main(int argc, char *argv[]){
    QCoreApplication app(argc, argv);
    MyServer *server=new MyServer;
    server->start(11111);
    //return  QCoreApplication::exec();//есть ли разница?
    return app.exec();
}
