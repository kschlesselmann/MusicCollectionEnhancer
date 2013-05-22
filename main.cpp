#include "replaygainenhancer.h"

#include <QDebug>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ReplayGainEnhancer rge(a.arguments().last());

    // Parsing command line options
    foreach (QString arg, a.arguments()) {
        if (arg.compare("-f") == 0) {
            qDebug() << "Forcing ReplayGain computation and overriding present values.";
            rge.setForceComputation(true);
        }
    }

    // Starting ReplayGain computation
    rge.process();

    return 0;
}
