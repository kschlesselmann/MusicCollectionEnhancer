#include "replaygainenhancer.h"

#include <QDebug>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ReplayGainEnhancer rge(a.arguments().last());

    // Parsing command line options
    // TODO Switch to more developed argument parser
    QStringList arguments = a.arguments();
    if (arguments.size() < 2) {
        arguments << "--help";
    }
    foreach (QString arg, arguments) {
        if (arg.compare("-f") == 0) {
            qDebug() << "Forcing ReplayGain computation and overriding present values.";
            rge.setForceComputation(true);
        } else if (arg.compare("--no-flac") == 0) {
            rge.setComputeFlac(false);
        } else if (arg.compare("--no-vorbis") == 0) {
            rge.setComputeVorbis(false);
        } else if (arg.compare("--no-mp3") == 0) {
            rge.setComputeMP3(false);
        } else if (arg.compare("-h") == 0 || arg.compare("--help") == 0) {
            qDebug() << "MusicCollectionEnhancer";
            qDebug() << "Usage: MusicCollectionEnhancer [Options] Directory";
            qDebug() << "Options:";
            qDebug() << "-f" << "Force ReplayGain computation even if values are present.";
            qDebug() << "--no-flac" << "Exclude flac (*.flac) files";
            qDebug() << "--no-vorbis" << "Exclude vorbis (*.ogg) files";
            qDebug() << "--no-mp3" << "Exclude mp3 (*.mp3) files";
            qDebug() << "-h, --help" << "Show this message";

            return 0;
        }
    }

    // Starting ReplayGain computation
    rge.process();

    return 0;
}
