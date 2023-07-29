#ifndef SOUNDPLAYER_HPP
#define SOUNDPLAYER_HPP

#include <QSound>
#include <QString>
#include <cstddef>
#include <qsound.h>
#include <string>
#include <thread>
#include <chrono>
#include <memory>

class SoundPlayerInterface {
    public:
    virtual void play(std::string filename) = 0;
    virtual void stop() = 0;
};

class SoundPlayer : public SoundPlayerInterface {
    QSound * qsound;
public:
    SoundPlayer() : qsound(nullptr) {}
    void play(std::string filename) {
        if (qsound != nullptr)
            delete qsound;
        qsound = new QSound(QString::fromStdString(filename));
        qsound->play();
    }
    void stop() {
        if (qsound != nullptr)
            qsound->stop();
    }
};

#endif