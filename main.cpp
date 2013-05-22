#include "replaygainenhancer.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ReplayGainEnhancer rge(a.arguments().at(1));
    rge.process();

    return a.exec();
}
