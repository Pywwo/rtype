/* Created by Antoine CARLIER on 25/11/2019 at 12:16. */

#include "LeaveLobbyDatagram.hpp"
#include "RequestStartGameDatagram.hpp"

#include "worlds/InLobbyWorld.hpp"
#include "worlds/WorldManager.hpp"

#include "NetworkSystem.hpp"

#include "utilities/AssetsManager.hpp"
#include "utilities/GameSettings.hpp"
#include "utilities/GameWrapper.hpp"

#include "components/Sprite.hpp"
#include "components/Transform.hpp"
#include "components/Text.hpp"
#include "components/Rectangle.hpp"
#include "components/Button.hpp"
#include "components/Parallax.hpp"

rtype::worlds::InLobbyWorld::InLobbyWorld(const std::string &name)
: World(name), _lobby()
{
    _entityManager.createEntity("background_in_lobby");
    _entityManager.createEntity("lobby_text");
    _entityManager.createEntity("lobby_text_player");
    _entityManager.createEntity("lobby_text_list_player");
    _entityManager.createEntity("lobby_ui_button_start");
    _entityManager.createEntity("lobby_ui_button_arrow_back");

    setupLobbyText();
    setupPlayerText();
    setupListPlayerText();
    setupStartButton();
    setupBackButton();
    setupBackground();
}

void rtype::worlds::InLobbyWorld::setupBackground()
{
    auto &assetsManager = rtype::utils::AssetsManager::getInstance();
    auto &gameSettings = rtype::utils::GameSettings::getInstance();

    auto backgroundEntity = _entityManager.getEntityByName("background_in_lobby");
    backgroundEntity->assignComponent("Sprite", new rtype::components::Sprite(*backgroundEntity, assetsManager["menu_background"]));
    backgroundEntity->assignComponent("Transform", new rtype::components::Transform(*backgroundEntity));
    backgroundEntity->assignComponent("Rectangle", new rtype::components::Rectangle(*backgroundEntity, 0, 0, 1332, 850));
    backgroundEntity->assignComponent("Parallax", new rtype::components::Parallax(*backgroundEntity, 100));

    auto backgroundSpriteComponent = dynamic_cast<rtype::components::Sprite *>(backgroundEntity->getComponent("Sprite"));
    auto backgroundTransformComponent = dynamic_cast<rtype::components::Transform *>(backgroundEntity->getComponent("Transform"));

    backgroundTransformComponent->setPosition(gameSettings.getWidth() / 2, gameSettings.getHeight() / 2);
    backgroundSpriteComponent->setRepeated(true);
}

void rtype::worlds::InLobbyWorld::setupLobbyText()
{
    auto &assetsManager = rtype::utils::AssetsManager::getInstance();
    auto &gameSettings = rtype::utils::GameSettings::getInstance();

    auto LobbyTextEntity = _entityManager.getEntityByName("lobby_text");
    LobbyTextEntity->assignComponent("Text", new rtype::components::Text(*LobbyTextEntity, 42, assetsManager["menu_font"]));
    LobbyTextEntity->assignComponent("Transform", new rtype::components::Transform(*LobbyTextEntity));

    auto textComponent = dynamic_cast<rtype::components::Text *>(LobbyTextEntity->getComponent("Text"));
    textComponent->setString("LOBBY #" + std::to_string(_lobby.id));
    textComponent->setColor(sf::Color::White);

    auto textTransform = dynamic_cast<rtype::components::Transform *>(LobbyTextEntity->getComponent("Transform"));
    textTransform->setPosition(gameSettings.getWidth() / 2 - 250, 30);
}

void rtype::worlds::InLobbyWorld::setupPlayerText()
{
    auto &assetsManager = rtype::utils::AssetsManager::getInstance();
    auto &gameSettings = rtype::utils::GameSettings::getInstance();

    auto lobbyTextEntity = _entityManager.getEntityByName("lobby_text_player");
    lobbyTextEntity->assignComponent("Text", new rtype::components::Text(*lobbyTextEntity, 42, assetsManager["menu_font"]));
    lobbyTextEntity->assignComponent("Transform", new rtype::components::Transform(*lobbyTextEntity));

    auto textComponent = dynamic_cast<rtype::components::Text *>(lobbyTextEntity->getComponent("Text"));
    textComponent->setString("PLAYERS:");
    textComponent->setColor(sf::Color(51, 204, 255));

    auto textTransform = dynamic_cast<rtype::components::Transform *>(lobbyTextEntity->getComponent("Transform"));
    textTransform->setPosition(gameSettings.getWidth() / 2 - 100, 200);
}

void rtype::worlds::InLobbyWorld::setupListPlayerText()
{
    auto &gameSettings = rtype::utils::GameSettings::getInstance();
    std::string toSet;

    for (auto &it : _lobby.player)
        toSet += (it.id != 0) ? ("- " + std::string(it.name) + "\n") : "";

    auto LobbyTextEntity = _entityManager.getEntityByName("lobby_text_list_player");
    LobbyTextEntity->assignComponent("Text", new rtype::components::Text(*LobbyTextEntity));
    LobbyTextEntity->assignComponent("Transform", new rtype::components::Transform(*LobbyTextEntity));

    auto textComponent = dynamic_cast<rtype::components::Text *>(LobbyTextEntity->getComponent("Text"));
    textComponent->setString(toSet);
    textComponent->setColor(sf::Color(153, 204, 255));

    auto textTransform = dynamic_cast<rtype::components::Transform *>(LobbyTextEntity->getComponent("Transform"));
    textTransform->setPosition(gameSettings.getWidth() / 2 - 100, 250);
}

void rtype::worlds::InLobbyWorld::setLobby(const Lobby &lobby)
{
    _lobby = lobby;
    setupListPlayerText();
    setupLobbyText();
}

void rtype::worlds::InLobbyWorld::setupStartButton()
{
    auto &assetsManager = rtype::utils::AssetsManager::getInstance();
    auto &gameSettings = rtype::utils::GameSettings::getInstance();

    auto uiLobbyButtonStart = _entityManager.getEntityByName("lobby_ui_button_start");
    uiLobbyButtonStart->assignComponent("Sprite", new rtype::components::Sprite(*uiLobbyButtonStart, assetsManager["start_button"]));
    uiLobbyButtonStart->assignComponent("Transform", new rtype::components::Transform(*uiLobbyButtonStart));
    uiLobbyButtonStart->assignComponent("Rectangle", new rtype::components::Rectangle(*uiLobbyButtonStart, 0, 0, 500, 100));
    uiLobbyButtonStart->assignComponent("Button", new rtype::components::Button(*uiLobbyButtonStart, [this]() {
        auto networkSystem = dynamic_cast<rtype::systems::NetworkSystem *>(rtype::utils::GameWrapper::getInstance().getSystemManager().getSystem("Network System"));
        rtype::network::RequestStartGameDatagram rsgd;
        rsgd.createRequestStartGameDatagram(networkSystem->getUserId(), _lobby.id);
        networkSystem->send(rsgd);
    }));

    auto buttonStartTransform = dynamic_cast<rtype::components::Transform *>(uiLobbyButtonStart->getComponent("Transform"));
    buttonStartTransform->setPosition(gameSettings.getWidth() / 2, gameSettings.getHeight() - 100);
}

void rtype::worlds::InLobbyWorld::setupBackButton()
{
    auto &worldManager = rtype::worlds::WorldManager::getInstance();
    auto &assetsManager = rtype::utils::AssetsManager::getInstance();

    auto uiBackArrowButton = _entityManager.getEntityByName("lobby_ui_button_arrow_back");
    uiBackArrowButton->assignComponent("Sprite", new rtype::components::Sprite(*uiBackArrowButton, assetsManager["back_arrow_button"]));
    uiBackArrowButton->assignComponent("Transform", new rtype::components::Transform(*uiBackArrowButton));
    uiBackArrowButton->assignComponent("Rectangle", new rtype::components::Rectangle(*uiBackArrowButton, 0, 0, 100, 100));
    uiBackArrowButton->assignComponent("Button", new rtype::components::Button(*uiBackArrowButton, [&worldManager, this]() {
        auto networkSystem = dynamic_cast<rtype::systems::NetworkSystem *>(rtype::utils::GameWrapper::getInstance().getSystemManager().getSystem("Network System"));
        rtype::network::LeaveLobbyDatagram lld;

        lld.createLeaveLobbyDatagram(networkSystem->getUserId(), _lobby.id);

        networkSystem->send(lld);

        worldManager.changeWorld("Lobby List World");
    }));

    auto buttonBackArrowTransform = dynamic_cast<rtype::components::Transform *>(uiBackArrowButton->getComponent("Transform"));
    buttonBackArrowTransform->setPosition(100, 150);
}