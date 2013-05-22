#include "replaygainenhancer.h"

#include <QCoreApplication>
#include <QDebug>
#include <QProcess>
#include <QtConcurrentMap>

#include <boost/bind.hpp>

ReplayGainEnhancer::ReplayGainEnhancer(const QString &path) :
    _baseDirectory(path),
    _flacFilter("*.flac"),
    _vorbisFilter("*.ogg"),
    _mp3Filter("*.mp3")
{
    qDebug() << "Ideal thread count is:" << QThread::idealThreadCount();
}

void ReplayGainEnhancer::process()
{
    if (_baseDirectory.exists()) {
        processDirectory(_baseDirectory);
        computeReplayGain();
        waitForFinish();
    } else {
        qWarning() << _baseDirectory.absolutePath() << "does not exist. Exiting.";
    }
}

void ReplayGainEnhancer::processDirectory(const QDir &directory)
{
    foreach (QFileInfo dir, directory.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs)) {
        processDirectory(QDir(dir.absoluteFilePath()));
    }

    processFiles(directory, _flacFiles, _flacFilter);
    processFiles(directory, _vorbisFiles, _vorbisFilter);
    processFiles(directory, _mp3Files, _mp3Filter);
}

void ReplayGainEnhancer::processFiles(const QDir &directory, QList<QList<QFileInfo> > &albumList, const QStringList &fileFilter)
{
    QList<QFileInfo> albumFiles;
    foreach (QFileInfo file, directory.entryInfoList(fileFilter, QDir::Files)) {
        albumFiles.append(file);
    }

    if (!albumFiles.isEmpty()) {
        albumList.append(albumFiles);
    }
}

void ReplayGainEnhancer::computeReplayGain()
{
    QFuture<void> flacFuture = QtConcurrent::map(_flacFiles, boost::bind(&ReplayGainEnhancer::processAlbum, this, _1, TYPE_FLAC));
    _flacWatcher.setFuture(flacFuture);

    QFuture<void> vorbisFuture = QtConcurrent::map(_vorbisFiles, boost::bind(&ReplayGainEnhancer::processAlbum, this, _1, TYPE_VORBIS));
    _vorbisWatcher.setFuture(vorbisFuture);

    QFuture<void> mp3Future = QtConcurrent::map(_mp3Files, boost::bind(&ReplayGainEnhancer::processAlbum, this, _1, TYPE_MP3));
    _mp3Watcher.setFuture(mp3Future);
}

void ReplayGainEnhancer::processAlbum(const QList<QFileInfo> &album, FileType type)
{
    qDebug() << "Starting replaygain computation for" << album.first().absolutePath();

    QString program;
    QStringList args;
    switch (type) {
    case TYPE_FLAC: {
        program = "metaflac";
        args << "--no-utf8-convert" << "--add-replay-gain";
        break;
    } case TYPE_VORBIS: {
        program = "vorbisgain";
        args << "-as";
        break;
    } case TYPE_MP3: {
        program = "mp3gain";
        args << "-a" << "-s" << "i";
        break;
    } default:
        break;
    }

    foreach (QFileInfo file, album) {
        args << file.absoluteFilePath().replace("\"", "\\\"");
    }

    QProcess process;
    process.start("metaflac", args);
    process.waitForFinished(-1);
}

void ReplayGainEnhancer::waitForFinish()
{
    _flacWatcher.waitForFinished();
    _vorbisWatcher.waitForFinished();
    _mp3Watcher.waitForFinished();

    qApp->quit();
}
