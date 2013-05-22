#ifndef REPLAYGAINENHANCER_H
#define REPLAYGAINENHANCER_H

#include <QDir>
#include <QFileInfo>
#include <QFutureWatcher>
#include <QList>
#include <QString>
#include <QStringList>

class ReplayGainEnhancer
{
public:
    ReplayGainEnhancer(const QString &path);

    void process();

    void setForceComputation(bool force);

private:
    enum FileType {
        TYPE_FLAC,
        TYPE_VORBIS,
        TYPE_MP3
    };

    QDir _baseDirectory;

    bool _forceComputation;

    QStringList _flacFilter;
    QList<QList<QFileInfo> > _flacFiles;

    QStringList _vorbisFilter;
    QList<QList<QFileInfo> > _vorbisFiles;

    QStringList _mp3Filter;
    QList<QList<QFileInfo> > _mp3Files;

    QFutureWatcher<void> _flacWatcher;
    QFutureWatcher<void> _vorbisWatcher;
    QFutureWatcher<void> _mp3Watcher;

    void processDirectory(const QDir &directory);
    void processFiles(const QDir &directory, QList<QList<QFileInfo> > &albumList, const QStringList &fileFilter);
    void computeReplayGain();
    void processAlbum(const QList<QFileInfo> &album, FileType type);

    void waitForFinish();
};

inline void ReplayGainEnhancer::setForceComputation(bool force)
{
    _forceComputation = force;
}

#endif // REPLAYGAINENHANCER_H
