
/* Created by Romain FOUYER on 25/11/2019 at 11:39. */

#include "CreateLobbyDatagram.hpp"
#include "ConnectLobbyDatagram.hpp"

#include "systems/SystemManager.hpp"
#include "NetworkSystem.hpp"

#include "worlds/InLobbyWorld.hpp"
#include "worlds/WorldManager.hpp"
#include "worlds/LobbyListWorld.hpp"

#include "utilities/AssetsManager.hpp"
#include "utilities/GameSettings.hpp"
#include "utilities/GameWrapper.hpp"

#include "components/Sprite.hpp"
#include "components/Transform.hpp"
#include "components/Rectangle.hpp"
#include "components/Button.hpp"
#include "components/Text.hpp"
#include "components/Parallax.hpp"

rtype::worlds::LobbyListWorld::LobbyListWorld(const std::string &name)
: World(name)
{
    _entityManager.createEntity("background");
    _entityManager.createEntity("back");
    _entityManager.createEntity("create");

    setupUI();
}

void rtype::worlds::LobbyListWorld::setupUI()
{
    auto &worldManager = rtype::worlds::WorldManager::getInstance();
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

    auto backEntity = _entityManager.getEntityByName("back");
    backEntity->assignComponent("Sprite", new rtype::components::Sprite(*backEntity, assetsManager["back_arrow_button"]));
    backEntity->assignComponent("Transform", new rtype::components::Transform(*backEntity));
    backEntity->assignComponent("Rectangle", new rtype::components::Rectangle(*backEntity, 0, 0, 100, 100));
    backEntity->assignComponent("Button", new rtype::components::Button(*backEntity, [&worldManager]() {
        worldManager.changeWorld("Menu World");
    }));

    auto backButtonTransform = dynamic_cast<rtype::components::Transform *>(backEntity->getComponent("Transform"));
    backButtonTransform->setPosition(100, 150);

    auto createEntity = _entityManager.getEntityByName("create");
    createEntity->assignComponent("Sprite", new rtype::components::Sprite(*createEntity, assetsManager["create_lobby"]));
    createEntity->assignComponent("Transform", new rtype::components::Transform(*createEntity));
    createEntity->assignComponent("Rectangle", new rtype::components::Rectangle(*createEntity, 0, 0, 500, 100));
    createEntity->assignComponent("Button", new rtype::components::Button(*createEntity, [&worldManager]() {
        auto networkSystem = dynamic_cast<rtype::systems::NetworkSystem *>(rtype::utils::GameWrapper::getInstance().getSystemManager().getSystem("Network System"));
        rtype::network::CreateLobbyDatagram cld;

        cld.createCreateLobbyDatagram(networkSystem->getUserId());

        networkSystem->send(cld);
        worldManager.changeWorld("In Lobby World");
    }));

    auto createButtonTransform = dynamic_cast<rtype::components::Transform *>(createEntity->getComponent("Transform"));
    createButtonTransform->setPosition(600, 150);
}

void rtype::worlds::LobbyListWorld::setNewLobbies(std::vector<Lobby> &newLobbies)
{
    for (unsigned long lobbyIndex = 0; lobbyIndex < _lobbies.size(); ++lobbyIndex) {
        _entityManager.deleteEntity("lobbyidtext" + std::to_string(lobbyIndex));
        _entityManager.deleteEntity("lobbyplayertext" + std::to_string(lobbyIndex));
        _entityManager.deleteEntity("lobby" + std::to_string(lobbyIndex));
    }

    _lobbies = newLobbies;

    for (unsigned long lobbyIndex = 0; lobbyIndex < _lobbies.size(); ++lobbyIndex) {
        _entityManager.createEntity("lobby" + std::to_string(lobbyIndex));
        setupLobbyComponents(lobbyIndex, _lobbies[lobbyIndex]);
    }
}

void rtype::worlds::LobbyListWorld::setupLobbyComponents(unsigned long lobbyIndex, const Lobby &lobby)
{
    auto &worldManager = rtype::worlds::WorldManager::getInstance();
    auto &gameSettings = rtype::utils::GameSettings::getInstance();
    auto &assetsManager = rtype::utils::AssetsManager::getInstance();
    auto currentLobbyEntity = _entityManager.getEntityByName("lobby" + std::to_string(lobbyIndex));

    currentLobbyEntity->assignComponent("Sprite", new rtype::components::Sprite(*currentLobbyEntity, assetsManager["sample_button"]));
    currentLobbyEntity->assignComponent("Transform", new rtype::components::Transform(*currentLobbyEntity));
    currentLobbyEntity->assignComponent("Rectangle", new rtype::components::Rectangle(*currentLobbyEntity, 0, 0, 1000, 100));
    currentLobbyEntity->assignComponent("Button", new rtype::components::Button(*currentLobbyEntity, [&worldManager, lobby]() {
        unsigned int playerNumber = 0;

        for (auto &it : lobby.player) {
            if (it.id != 0)
                ++playerNumber;
        }
        if (playerNumber == 4)
            return;
        auto networkSystem = dynamic_cast<rtype::systems::NetworkSystem *>(rtype::utils::GameWrapper::getInstance().getSystemManager().getSystem("Network System"));
        rtype::network::ConnectLobbyDatagram cld;

        cld.createConnectLobbyDatagram(networkSystem->getUserId(), lobby.id);

        networkSystem->send(cld);
    }));
    auto currentLobbyRectangle = dynamic_cast<rtype::components::Rectangle *>(currentLobbyEntity->getComponent("Rectangle"));

    auto currentLobbyTransform = dynamic_cast<rtype::components::Transform *>(currentLobbyEntity->getComponent("Transform"));

    int totalHeight = currentLobbyRectangle->getHeight() * 3;

    currentLobbyTransform->setPosition(gameSettings.getWidth() / 2, (totalHeight / 2) + (100 * (1 + lobbyIndex)) + 20);

    // Setup text id

    _entityManager.createEntity("lobbyidtext" + std::to_string(lobbyIndex));

    auto lobbyTextEntity = _entityManager.getEntityByName("lobbyidtext" + std::to_string(lobbyIndex));

    lobbyTextEntity->assignComponent("Text", new rtype::components::Text(*lobbyTextEntity, 42, assetsManager["menu_font"]));

    auto textComponent = dynamic_cast<rtype::components::Text *>(lobbyTextEntity->getComponent("Text"));
    textComponent->setString("#" + std::to_string(lobby.id));

    lobbyTextEntity->assignComponent("Transform", new rtype::components::Transform(*lobbyTextEntity));
    auto textTransform = dynamic_cast<rtype::components::Transform *>(lobbyTextEntity->getComponent("Transform"));

    textTransform->setPosition(gameSettings.getWidth() / 2 - 450, (totalHeight / 2) + (100 * (1 + lobbyIndex)) - 140);

    // Setup text player

    _entityManager.createEntity("lobbyplayertext" + std::to_string(lobbyIndex));

    auto lobbyPlayerTextEntity = _entityManager.getEntityByName("lobbyplayertext" + std::to_string(lobbyIndex));

    lobbyPlayerTextEntity->assignComponent("Text", new rtype::components::Text(*lobbyTextEntity, 42, assetsManager["menu_font"]));

    auto textPlayerComponent = dynamic_cast<rtype::components::Text *>(lobbyPlayerTextEntity->getComponent("Text"));

    unsigned int playerNumber = 0;

    for (int i = 0; i < 4; i++)
        if (lobby.player[i].id != 0)
            playerNumber++;
    textPlayerComponent->setString(std::to_string(playerNumber) + " / 4");

    lobbyPlayerTextEntity->assignComponent("Transform", new rtype::components::Transform(*lobbyTextEntity));
    auto textPlayerTransform = dynamic_cast<rtype::components::Transform *>(lobbyPlayerTextEntity->getComponent("Transform"));

    textPlayerTransform->setPosition(gameSettings.getWidth() / 2 + 350, (totalHeight / 2) + (100 * (1 + lobbyIndex)) - 140);
}