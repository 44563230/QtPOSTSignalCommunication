#include "serverconfiguration.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerConfiguration s;
    s.show();
    return a.exec();
}
