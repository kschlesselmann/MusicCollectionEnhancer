MusicCollectionEnhancer
=======================

A little tool that performs various task on a music collection directory

This is still beta status missing a lot of validations and output messages. Use at your own risk.

Usage
----------------------
Currently there is just ReplayGain computation supported.

MusicCollectionEnhancer [Options] Directory

Options:
* **-f** Force ReplayGain computation even if values are present
* **--no-flac** Exclude Flac files
* **--no-vorbis** Exclude Vorbis files
* **--no-mp3** Exclude MP3 files
