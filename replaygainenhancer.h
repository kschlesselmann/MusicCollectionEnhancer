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
    void setComputeFlac(bool compute);
    void setComputeVorbis(bool compute);
    void setComputeMP3(bool compute);

private:
    enum FileType {
        TYPE_FLAC,
        TYPE_VORBIS,
        TYPE_MP3
    };

    QDir _baseDirectory;

    bool _forceComputation;
    bool _computeFlac;
    bool _computeVorbis;
    bool _computeMP3;

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

inline void ReplayGainEnhancer::setComputeFlac(bool compute)
{
    _computeFlac = compute;
}

inline void ReplayGainEnhancer::setComputeVorbis(bool compute)
{
    _computeVorbis = compute;
}

inline void ReplayGainEnhancer::setComputeMP3(bool compute)
{
    _computeMP3 = compute;
}

#endif // REPLAYGAINENHANCER_H
