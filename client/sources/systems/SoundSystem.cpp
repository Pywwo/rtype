
/* Created by Romain FOUYER on 19/11/2019 at 15:38. */

#include "SoundSystem.hpp"

#include "worlds/WorldManager.hpp"
#include "components/Sound.hpp"

rtype::systems::SoundSystem::SoundSystem(const std::string &name)
: System(name), _effectVolume(100), _musicVolume(100), _currentWorld("")
{

}

void rtype::systems::SoundSystem::onInit()
{
    auto &worldManager = rtype::worlds::WorldManager::getInstance();

    _currentWorld = worldManager.getCurrentWorld()->getWorldName();
}

void rtype::systems::SoundSystem::onUpdate([[maybe_unused]] float elapsedTime)
{
    auto &worldManager = rtype::worlds::WorldManager::getInstance();

    if (_currentWorld != worldManager.getCurrentWorld()->getWorldName()) {
        worldManager.getWorldByName(_currentWorld)->getEntityManager().applyToEach(std::vector<std::string>({"Sound"}), [](ecs::entities::Entity *entity) {
            auto music = dynamic_cast<rtype::components::Sound *>(entity->getComponent("Sound"));
            music->stop();
        });

        _currentWorld = worldManager.getCurrentWorld()->getWorldName();
    }

    worldManager.getCurrentWorld()->getEntityManager().applyToEach(std::vector<std::string>({"Sound"}), [this](ecs::entities::Entity *entity) {
        auto music = dynamic_cast<rtype::components::Sound *>(entity->getComponent("Sound"));
        if (music->getType() == rtype::components::SoundType::MUSIC)
            music->setVolume(_musicVolume);
        else
            music->setVolume(_effectVolume);
        music->play();
    });
}

void rtype::systems::SoundSystem::onClose()
{
}

float rtype::systems::SoundSystem::getEffectVolume() const {
    return _effectVolume;
}

void rtype::systems::SoundSystem::setEffectVolume(float effectVolume) {
    _effectVolume = effectVolume;
}

float rtype::systems::SoundSystem::getMusicVolume() const {
    return _musicVolume;
}

void rtype::systems::SoundSystem::setMusicVolume(float musicVolume) {
    _musicVolume = musicVolume;
}
