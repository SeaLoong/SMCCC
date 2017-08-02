#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include "smccc.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SMCCC *Core = new SMCCC;
    Core->setDotMinecraftDirPath(QDir::currentPath() + "/.minecraft");
    Core->setVersion("1.12");

    Core->setAssetsCheck(false);
    Core->setFileCheck(false);

    Core->set_username("DemoPlayer");

    qDebug()<<Core->processLaunchArgs();
    qDebug()<<Core->getLaunchArgsString();

    return a.exec();
}
