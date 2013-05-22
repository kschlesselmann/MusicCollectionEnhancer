#include "replaygainenhancer.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ReplayGainEnhancer rge(a.arguments().at(1));
    // TODO add command line option to set force mode
    rge.process();

    return 0;
}
