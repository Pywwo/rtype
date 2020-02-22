
/* Created by Romain FOUYER on 19/11/2019 at 12:22. */


#include "Sound.hpp"

#include "exception/RtypeException.hpp"

rtype::components::Sound::Sound(ecs::entities::Entity &entity, const std::string &path, rtype::components::SoundType type)
: Component(entity), _state(rtype::components::SoundState::STOPPED), _type(type), _music()
{
    if (!_music.openFromFile(path))
        throw rtype::ComponentException("Failed to load: " + path);
}

rtype::components::Sound::~Sound()
{
    _music.stop();
}

void rtype::components::Sound::play()
{
    if (_state == rtype::components::SoundState::STOPPED) {
        _music.play();
        _state = rtype::components::SoundState::PLAYING;
    }
}

void rtype::components::Sound::stop()
{
    if (_state == rtype::components::SoundState::PLAYING) {
        _music.stop();
        _state = rtype::components::SoundState::STOPPED;
    }
}

void rtype::components::Sound::pause()
{
    _music.pause();
}

void rtype::components::Sound::restart()
{
    stop();
    play();
}

rtype::components::SoundType rtype::components::Sound::getType() const
{
    return _type;
}

void rtype::components::Sound::setVolume(float volume) {
    _music.setVolume(volume);
}



