
/* Created by Romain FOUYER on 27/11/2019 at 14:06. */

#include <sstream>
#include "utilities/GameWrapper.hpp"

#include "systems/SoundSystem.hpp"

#include "worlds/WorldManager.hpp"
#include "worlds/SettingsWorld.hpp"

#include "utilities/AssetsManager.hpp"
#include "utilities/GameSettings.hpp"

#include "components/Sprite.hpp"
#include "components/Transform.hpp"
#include "components/Rectangle.hpp"
#include "components/Parallax.hpp"
#include "components/Text.hpp"
#include "components/Button.hpp"

rtype::worlds::SettingsWorld::SettingsWorld(const std::string &name)
: World(name)
{
    _entityManager.createEntity("background");
    _entityManager.createEntity("lobby_ui_button_arrow_back");
    _entityManager.createEntity("down_music_volume_button");
    _entityManager.createEntity("up_music_volume_button");
    _entityManager.createEntity("down_effect_volume_button");
    _entityManager.createEntity("up_effect_volume_button");
    _entityManager.createEntity("music_volume_text");
    _entityManager.createEntity("effect_volume_text");
    _entityManager.createEntity("music_ui");
    _entityManager.createEntity("effect_ui");

    setupBackground();
    setupBackButton();
    setupMusicVolumeChanger();
    setupEffectVolumeChanger();
}

void rtype::worlds::SettingsWorld::setupBackground()
{
    auto &assetsManager = rtype::utils::AssetsManager::getInstance();
    auto &gameSettings = rtype::utils::GameSettings::getInstance();

    auto backgroundEntity = _entityManager.getEntityByName("background");

    backgroundEntity->assignComponent("Sprite", new rtype::components::Sprite(*backgroundEntity, assetsManager["menu_background"]));
    backgroundEntity->assignComponent("Transform", new rtype::components::Transform(*backgroundEntity));
    backgroundEntity->assignComponent("Rectangle", new rtype::components::Rectangle(*backgroundEntity, 0, 0, 1332, 850));
    backgroundEntity->assignComponent("Parallax", new rtype::components::Parallax(*backgroundEntity, 100));

    auto backgroundSpriteComponent = dynamic_cast<rtype::components::Sprite *>(backgroundEntity->getComponent("Sprite"));
    auto backgroundTransformComponent = dynamic_cast<rtype::components::Transform *>(backgroundEntity->getComponent("Transform"));

    backgroundTransformComponent->setPosition(gameSettings.getWidth() / 2, gameSettings.getHeight() / 2);
    backgroundSpriteComponent->setRepeated(true);
}

void rtype::worlds::SettingsWorld::setupBackButton()
{
    auto &worldManager = rtype::worlds::WorldManager::getInstance();
    auto &assetsManager = rtype::utils::AssetsManager::getInstance();

    auto uiBackArrowButton = _entityManager.getEntityByName("lobby_ui_button_arrow_back");
    uiBackArrowButton->assignComponent("Sprite", new rtype::components::Sprite(*uiBackArrowButton, assetsManager["back_arrow_button"]));
    uiBackArrowButton->assignComponent("Transform", new rtype::components::Transform(*uiBackArrowButton));
    uiBackArrowButton->assignComponent("Rectangle", new rtype::components::Rectangle(*uiBackArrowButton, 0, 0, 100, 100));
    uiBackArrowButton->assignComponent("Button", new rtype::components::Button(*uiBackArrowButton, [&worldManager]() {
        worldManager.changeWorld("Menu World");
    }));

    auto buttonBackArrowTransform = dynamic_cast<rtype::components::Transform *>(uiBackArrowButton->getComponent("Transform"));
    buttonBackArrowTransform->setPosition(100, 150);
}

void rtype::worlds::SettingsWorld::setupMusicVolumeChanger()
{
    auto &assetsManager = rtype::utils::AssetsManager::getInstance();
    auto &gameSettings = rtype::utils::GameSettings::getInstance();

    // Music Volume Part

    auto musicUi = _entityManager.getEntityByName("music_ui");

    musicUi->assignComponent("Text", new rtype::components::Text(*musicUi, 42, assetsManager["menu_font"]));
    musicUi->assignComponent("Transform", new rtype::components::Transform(*musicUi));

    auto musicTextComponentUi = dynamic_cast<rtype::components::Text *>(musicUi->getComponent("Text"));
    auto musicTransformUi = dynamic_cast<rtype::components::Transform *>(musicUi->getComponent("Transform"));

    musicTextComponentUi->setColor(sf::Color::White);
    musicTextComponentUi->setString("MUSIC VOLUME");
    musicTransformUi->setPosition(gameSettings.getWidth() / 2 - 175, gameSettings.getHeight() / 2 - 220);

    auto upMusicVolumeButton = _entityManager.getEntityByName("up_music_volume_button");

    upMusicVolumeButton->assignComponent("Sprite", new rtype::components::Sprite(*upMusicVolumeButton, assetsManager["back_arrow_button"]));
    upMusicVolumeButton->assignComponent("Transform", new rtype::components::Transform(*upMusicVolumeButton));
    upMusicVolumeButton->assignComponent("Rectangle", new rtype::components::Rectangle(*upMusicVolumeButton, 0, 0, 100, 100));
    upMusicVolumeButton->assignComponent("Button", new rtype::components::Button(*upMusicVolumeButton, [this]() {
        auto soundSystem = dynamic_cast<rtype::systems::SoundSystem *>(rtype::utils::GameWrapper::getInstance().getSystemManager().getSystem("Sound System"));

        if (soundSystem->getMusicVolume() < 100)
            soundSystem->setMusicVolume(soundSystem->getMusicVolume() + 5);
        updateString();
    }));

    auto upMusicVolumeTransform = dynamic_cast<rtype::components::Transform *>(upMusicVolumeButton->getComponent("Transform"));

    upMusicVolumeTransform->setPosition(gameSettings.getWidth() / 2 + 200, gameSettings.getHeight() / 2);
    upMusicVolumeTransform->setScale(-1, 1);

    auto downMusicVolumeButton = _entityManager.getEntityByName("down_music_volume_button");

    downMusicVolumeButton->assignComponent("Sprite", new rtype::components::Sprite(*downMusicVolumeButton, assetsManager["back_arrow_button"]));
    downMusicVolumeButton->assignComponent("Transform", new rtype::components::Transform(*downMusicVolumeButton));
    downMusicVolumeButton->assignComponent("Rectangle", new rtype::components::Rectangle(*downMusicVolumeButton, 0, 0, 100, 100));
    downMusicVolumeButton->assignComponent("Button", new rtype::components::Button(*downMusicVolumeButton, [this]() {
        auto soundSystem = dynamic_cast<rtype::systems::SoundSystem *>(rtype::utils::GameWrapper::getInstance().getSystemManager().getSystem("Sound System"));

        if (soundSystem->getMusicVolume() > 0)
            soundSystem->setMusicVolume(soundSystem->getMusicVolume() - 5);
        updateString();
    }));

    auto downMusicVolumeTransform = dynamic_cast<rtype::components::Transform *>(downMusicVolumeButton->getComponent("Transform"));

    downMusicVolumeTransform->setPosition(gameSettings.getWidth() / 2 - 200, gameSettings.getHeight() / 2);

    auto musicVolumeText = _entityManager.getEntityByName("music_volume_text");

    musicVolumeText->assignComponent("Text", new rtype::components::Text(*musicVolumeText));
    musicVolumeText->assignComponent("Transform", new rtype::components::Transform(*musicVolumeText));

    auto musicVolumeTextComponent = dynamic_cast<rtype::components::Text *>(musicVolumeText->getComponent("Text"));
    auto musicVolumeTextTransform = dynamic_cast<rtype::components::Transform *>(musicVolumeText->getComponent("Transform"));

    std::ostringstream out;

    out.precision(0);
    out << std::fixed << dynamic_cast<rtype::systems::SoundSystem *>(rtype::utils::GameWrapper::getInstance().getSystemManager().getSystem("Sound System"))->getMusicVolume();

    musicVolumeTextComponent->setString(out.str());
    musicVolumeTextComponent->setColor(sf::Color::White);

    musicVolumeTextTransform->setPosition(gameSettings.getWidth() / 2 - 30, gameSettings.getHeight() / 2 - 120);
}

void rtype::worlds::SettingsWorld::setupEffectVolumeChanger()
{
    auto &assetsManager = rtype::utils::AssetsManager::getInstance();
    auto &gameSettings = rtype::utils::GameSettings::getInstance();

    // Music Volume Part

    auto musicUi = _entityManager.getEntityByName("effect_ui");

    musicUi->assignComponent("Text", new rtype::components::Text(*musicUi, 42, assetsManager["menu_font"]));
    musicUi->assignComponent("Transform", new rtype::components::Transform(*musicUi));

    auto musicTextComponentUi = dynamic_cast<rtype::components::Text *>(musicUi->getComponent("Text"));
    auto musicTransformUi = dynamic_cast<rtype::components::Transform *>(musicUi->getComponent("Transform"));

    musicTextComponentUi->setColor(sf::Color::White);
    musicTextComponentUi->setString("EFFECT VOLUME");
    musicTransformUi->setPosition(gameSettings.getWidth() / 2 - 175, gameSettings.getHeight() / 2 - 20);

    auto upMusicVolumeButton = _entityManager.getEntityByName("up_effect_volume_button");

    upMusicVolumeButton->assignComponent("Sprite", new rtype::components::Sprite(*upMusicVolumeButton, assetsManager["back_arrow_button"]));
    upMusicVolumeButton->assignComponent("Transform", new rtype::components::Transform(*upMusicVolumeButton));
    upMusicVolumeButton->assignComponent("Rectangle", new rtype::components::Rectangle(*upMusicVolumeButton, 0, 0, 100, 100));
    upMusicVolumeButton->assignComponent("Button", new rtype::components::Button(*upMusicVolumeButton, [this]() {
        auto soundSystem = dynamic_cast<rtype::systems::SoundSystem *>(rtype::utils::GameWrapper::getInstance().getSystemManager().getSystem("Sound System"));

        if (soundSystem->getEffectVolume() < 100)
            soundSystem->setEffectVolume(soundSystem->getEffectVolume() + 5);
        updateString();
    }));

    auto upMusicVolumeTransform = dynamic_cast<rtype::components::Transform *>(upMusicVolumeButton->getComponent("Transform"));

    upMusicVolumeTransform->setPosition(gameSettings.getWidth() / 2 + 200, gameSettings.getHeight() / 2 + 200);
    upMusicVolumeTransform->setScale(-1, 1);

    auto downMusicVolumeButton = _entityManager.getEntityByName("down_effect_volume_button");

    downMusicVolumeButton->assignComponent("Sprite", new rtype::components::Sprite(*downMusicVolumeButton, assetsManager["back_arrow_button"]));
    downMusicVolumeButton->assignComponent("Transform", new rtype::components::Transform(*downMusicVolumeButton));
    downMusicVolumeButton->assignComponent("Rectangle", new rtype::components::Rectangle(*downMusicVolumeButton, 0, 0, 100, 100));
    downMusicVolumeButton->assignComponent("Button", new rtype::components::Button(*downMusicVolumeButton, [this]() {
        auto soundSystem = dynamic_cast<rtype::systems::SoundSystem *>(rtype::utils::GameWrapper::getInstance().getSystemManager().getSystem("Sound System"));

        if (soundSystem->getEffectVolume() > 0)
            soundSystem->setEffectVolume(soundSystem->getEffectVolume() - 5);
        updateString();
    }));

    auto downMusicVolumeTransform = dynamic_cast<rtype::components::Transform *>(downMusicVolumeButton->getComponent("Transform"));

    downMusicVolumeTransform->setPosition(gameSettings.getWidth() / 2 - 200, gameSettings.getHeight() / 2 + 200);

    auto musicVolumeText = _entityManager.getEntityByName("effect_volume_text");

    musicVolumeText->assignComponent("Text", new rtype::components::Text(*musicVolumeText));
    musicVolumeText->assignComponent("Transform", new rtype::components::Transform(*musicVolumeText));

    auto musicVolumeTextComponent = dynamic_cast<rtype::components::Text *>(musicVolumeText->getComponent("Text"));
    auto musicVolumeTextTransform = dynamic_cast<rtype::components::Transform *>(musicVolumeText->getComponent("Transform"));

    std::ostringstream out;

    out.precision(0);
    out << std::fixed << dynamic_cast<rtype::systems::SoundSystem *>(rtype::utils::GameWrapper::getInstance().getSystemManager().getSystem("Sound System"))->getEffectVolume();

    musicVolumeTextComponent->setString(out.str());
    musicVolumeTextComponent->setColor(sf::Color::White);

    musicVolumeTextTransform->setPosition(gameSettings.getWidth() / 2 - 30, gameSettings.getHeight() / 2 + 90);
}

void rtype::worlds::SettingsWorld::updateString()
{
    auto musicVolumeText = _entityManager.getEntityByName("music_volume_text");

    auto musicVolumeTextComponent = dynamic_cast<rtype::components::Text *>(musicVolumeText->getComponent("Text"));

    std::ostringstream out;

    out.precision(0);
    out << std::fixed << dynamic_cast<rtype::systems::SoundSystem *>(rtype::utils::GameWrapper::getInstance().getSystemManager().getSystem("Sound System"))->getMusicVolume();

    musicVolumeTextComponent->setString(out.str());
    musicVolumeTextComponent->setColor(sf::Color::White);

    auto effectVolumeText = _entityManager.getEntityByName("effect_volume_text");

    auto effectVolumeTextComponent = dynamic_cast<rtype::components::Text *>(effectVolumeText->getComponent("Text"));

    std::ostringstream outs;

    outs.precision(0);
    outs << std::fixed << dynamic_cast<rtype::systems::SoundSystem *>(rtype::utils::GameWrapper::getInstance().getSystemManager().getSystem("Sound System"))->getEffectVolume();

    effectVolumeTextComponent->setString(outs.str());
    effectVolumeTextComponent->setColor(sf::Color::White);
}