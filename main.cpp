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
        } else if (arg.compare("--no-flac") == 0) {
            rge.setComputeFlac(false);
        } else if (arg.compare("--no-vorbis") == 0) {
            rge.setComputeVorbis(false);
        } else if (arg.compare("--no-mp3") == 0) {
            rge.setComputeMP3(false);
        }
    }

    // Starting ReplayGain computation
    rge.process();

    return 0;
}
