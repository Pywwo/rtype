
/* Created by Romain FOUYER on 18/11/2019 at 13:23. */

#include <network/datagram/ConnectServerDatagram.hpp>
#include "systems/SystemManager.hpp"

#include "FetchLobbiesDatagram.hpp"

#include "systems/NetworkSystem.hpp"

#include "utilities/AssetsManager.hpp"
#include "utilities/GameSettings.hpp"
#include "utilities/GameWrapper.hpp"

#include "worlds/MenuWorld.hpp"
#include "worlds/WorldManager.hpp"

#include "components/Sprite.hpp"
#include "components/Transform.hpp"
#include "components/Text.hpp"
#include "components/OpacityChanger.hpp"
#include "components/Rectangle.hpp"
#include "components/Parallax.hpp"
#include "components/Button.hpp"
#include "components/Sound.hpp"
#include "components/Input.hpp"

#include "DLLoader.hpp"

rtype::worlds::MenuWorld::MenuWorld(const std::string &name)
        : World(name)
{
    auto &assetsManager = rtype::utils::AssetsManager::getInstance();

    _entityManager.createEntity("background");
    _entityManager.createEntity("credit");
    _entityManager.createEntity("ui_logo");
    _entityManager.createEntity("ui_button_exit");
    _entityManager.createEntity("ui_button_play");
    _entityManager.createEntity("ui_button_settings");
    _entityManager.createEntity("ip_input_ui");
    _entityManager.createEntity("ip_input");
    _entityManager.createEntity("background_music");

    setupInput();

    auto backgroundMusicEntity = _entityManager.getEntityByName("background_music");
    backgroundMusicEntity->assignComponent("Sound", new rtype::components::Sound(*backgroundMusicEntity, assetsManager["menu_music"], rtype::components::SoundType::MUSIC));

    setupPlayButton();
    setupExitButton();
    setupSettingsButton();
    setupCredits();
    setupLogo();
    setupBackground();
}

rtype::worlds::MenuWorld::~MenuWorld() = default;

void rtype::worlds::MenuWorld::setupExitButton()
{
    auto &assetsManager = rtype::utils::AssetsManager::getInstance();
    auto &gameSettings = rtype::utils::GameSettings::getInstance();

    auto uiButtonExitEntity = _entityManager.getEntityByName("ui_button_exit");
    uiButtonExitEntity->assignComponent("Sprite", new rtype::components::Sprite(*uiButtonExitEntity, assetsManager["exit_button"], 0));
    uiButtonExitEntity->assignComponent("Transform", new rtype::components::Transform(*uiButtonExitEntity));
    uiButtonExitEntity->assignComponent("Rectangle", new rtype::components::Rectangle(*uiButtonExitEntity, 0, 0, 150, 50));
    uiButtonExitEntity->assignComponent("OpacityChanger", new rtype::components::OpacityChanger(*uiButtonExitEntity));
    uiButtonExitEntity->assignComponent("Button", new rtype::components::Button(*uiButtonExitEntity, [](void) {
        rtype::utils::GameWrapper::getInstance().getSystemManager().getSystem("SFML System")->onClose();
    }));

    auto buttonExitTransform = dynamic_cast<rtype::components::Transform *>(uiButtonExitEntity->getComponent("Transform"));
    buttonExitTransform->setPosition(gameSettings.getWidth() - 300, 275);
}

void rtype::worlds::MenuWorld::setupBackground()
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

void rtype::worlds::MenuWorld::setupLogo()
{
    auto &assetsManager = rtype::utils::AssetsManager::getInstance();
    auto &gameSettings = rtype::utils::GameSettings::getInstance();

    auto uiLogo = _entityManager.getEntityByName("ui_logo");
    uiLogo->assignComponent("Sprite", new rtype::components::Sprite(*uiLogo, assetsManager["logo"], 0));
    uiLogo->assignComponent("Transform", new rtype::components::Transform(*uiLogo));
    uiLogo->assignComponent("OpacityChanger", new rtype::components::OpacityChanger(*uiLogo));

    auto logoTransform = dynamic_cast<rtype::components::Transform *>(uiLogo->getComponent("Transform"));
    logoTransform->setPosition(gameSettings.getWidth() / 2, gameSettings.getHeight() / 2);
    logoTransform->setScale(1.5, 1.5);
}

void rtype::worlds::MenuWorld::setupPlayButton()
{
    auto &assetsManager = rtype::utils::AssetsManager::getInstance();
    auto &gameSettings = rtype::utils::GameSettings::getInstance();

    auto uiButtonPlayEntity = _entityManager.getEntityByName("ui_button_play");
    uiButtonPlayEntity->assignComponent("Sprite", new rtype::components::Sprite(*uiButtonPlayEntity, assetsManager["play_button"], 0));
    uiButtonPlayEntity->assignComponent("Transform", new rtype::components::Transform(*uiButtonPlayEntity));
    uiButtonPlayEntity->assignComponent("Rectangle", new rtype::components::Rectangle(*uiButtonPlayEntity, 0, 0, 150, 50));
    uiButtonPlayEntity->assignComponent("OpacityChanger", new rtype::components::OpacityChanger(*uiButtonPlayEntity));
    uiButtonPlayEntity->assignComponent("Button", new rtype::components::Button(*uiButtonPlayEntity, [this]() {
        _entityManager.getEntityByName("ip_input")->enable();
        _entityManager.getEntityByName("ip_input_ui")->enable();
    }));
    auto buttonPlayTransform = dynamic_cast<rtype::components::Transform *>(uiButtonPlayEntity->getComponent("Transform"));
    buttonPlayTransform->setPosition(gameSettings.getWidth() - 300, 125);
}

void rtype::worlds::MenuWorld::setupSettingsButton()
{
    auto &assetsManager = rtype::utils::AssetsManager::getInstance();
    auto &gameSettings = rtype::utils::GameSettings::getInstance();

    auto uiButtonSettingsEntity = _entityManager.getEntityByName("ui_button_settings");
    uiButtonSettingsEntity->assignComponent("Sprite", new rtype::components::Sprite(*uiButtonSettingsEntity, assetsManager["settings_button"], 0));
    uiButtonSettingsEntity->assignComponent("Transform", new rtype::components::Transform(*uiButtonSettingsEntity));
    uiButtonSettingsEntity->assignComponent("Rectangle", new rtype::components::Rectangle(*uiButtonSettingsEntity, 0, 0, 300, 50));
    uiButtonSettingsEntity->assignComponent("OpacityChanger", new rtype::components::OpacityChanger(*uiButtonSettingsEntity));
    uiButtonSettingsEntity->assignComponent("Button", new rtype::components::Button(*uiButtonSettingsEntity, []() {
        rtype::worlds::WorldManager::getInstance().changeWorld("Settings World");
    }));
    auto buttonSettingsTransform = dynamic_cast<rtype::components::Transform *>(uiButtonSettingsEntity->getComponent("Transform"));
    buttonSettingsTransform->setPosition(gameSettings.getWidth() - 237, 200);
}

void rtype::worlds::MenuWorld::setupInput()
{
    auto &gameSettings = rtype::utils::GameSettings::getInstance();
    auto &assetsManager = rtype::utils::AssetsManager::getInstance();

    auto ipInputDisplayEntity = _entityManager.getEntityByName("ip_input_ui");
    ipInputDisplayEntity->disable();
    ipInputDisplayEntity->assignComponent("Sprite", new rtype::components::Sprite(*ipInputDisplayEntity, assetsManager["ip_input_ui"]));
    ipInputDisplayEntity->assignComponent("Transform", new rtype::components::Transform(*ipInputDisplayEntity));

    auto inputDisplayTransform = reinterpret_cast<rtype::components::Transform *>(ipInputDisplayEntity->getComponent("Transform"));
    inputDisplayTransform->setPosition(gameSettings.getWidth() / 2, gameSettings.getHeight() / 2);

    auto ipInputEntity = _entityManager.getEntityByName("ip_input");
    ipInputEntity->disable();
    ipInputEntity->assignComponent("Input", new rtype::components::Input(*ipInputEntity));
    ipInputEntity->assignComponent("Transform", new rtype::components::Transform(*ipInputEntity));
    ipInputEntity->assignComponent("Text", new rtype::components::Text(*ipInputEntity));

    auto inputTransform = dynamic_cast<rtype::components::Transform *>(ipInputEntity->getComponent("Transform"));
    inputTransform->setPosition(gameSettings.getWidth() / 2 - 100, gameSettings.getHeight() / 2);

    auto inputComponent = dynamic_cast<rtype::components::Input *>(ipInputEntity->getComponent("Input"));
    inputComponent->setCallback([this, inputComponent]() {
        auto networkSystem = dynamic_cast<rtype::systems::NetworkSystem *>(rtype::utils::GameWrapper::getInstance().getSystemManager().getSystem("Network System"));

        _entityManager.getEntityByName("ip_input")->disable();
        _entityManager.getEntityByName("ip_input_ui")->disable();

        networkSystem->setNewIpAddress(inputComponent->getCurrentInput());

        rtype::network::ConnectServerDatagram csd;
        csd.createConnectServerDatagram(networkSystem->getUserId(), static_cast<int>(networkSystem->getReceivePort()));

        networkSystem->send(csd);
        
        rtype::network::FetchLobbiesDatagram fld;
        fld.createFetchLobbiesDatagram(networkSystem->getUserId());

        networkSystem->send(fld);
    });
}

void rtype::worlds::MenuWorld::setupCredits()
{
    auto &assetsManager = rtype::utils::AssetsManager::getInstance();
    auto creditEntity = _entityManager.getEntityByName("credit");

    creditEntity->assignComponent("Text", new rtype::components::Text(*creditEntity, 28, assetsManager["menu_font"]));
    creditEntity->assignComponent("Transform", new rtype::components::Transform(*creditEntity));

    auto creditTransform = dynamic_cast<rtype::components::Transform *>(creditEntity->getComponent("Transform"));
    auto creditText = dynamic_cast<rtype::components::Text *>(creditEntity->getComponent("Text"));

    creditText->setOpacity(0);
    creditEntity->assignComponent("OpacityChanger", new rtype::components::OpacityChanger(*creditEntity));

    creditText->setString("JULES BULTEAU - ANTOINE CARLIER\nCHARLIE JEANNEAU - ROMAIN FOUYER");
    creditText->setColor(sf::Color::White);
    creditTransform->setPosition(160, 480);
}