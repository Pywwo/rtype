/* Created by Romain FOUYER on 20/11/2019 at 16:24. */

#include "NetworkSystem.hpp"

#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/lexical_cast.hpp>

#include "network/datagram/StartGameDatagram.hpp"
#include "network/datagram/FetchLobbiesDatagram.hpp"
#include "network/datagram/AvailableLobbiesDatagram.hpp"
#include "network/datagram/LobbyInfosDatagram.hpp"
#include "network/datagram/UpdateComponentsDatagram.hpp"
#include "network/datagram/DeletePlayerDatagram.hpp"
#include "network/datagram/SpawnEnemyDatagram.hpp"
#include "network/datagram/EndGameDatagram.hpp"
#include "network/datagram/StartGameDatagram.hpp"

#include "worlds/WorldManager.hpp"
#include "worlds/InLobbyWorld.hpp"
#include "worlds/LobbyListWorld.hpp"
#include "worlds/GameWorld.hpp"

#include "components/Controller.hpp"
#include "components/Transform.hpp"
#include "components/Sprite.hpp"
#include "components/Status.hpp"
#include "components/Animator.hpp"
#include "components/Timer.hpp"
#include "components/Rectangle.hpp"

#include "utilities/GameSettings.hpp"
#include "utilities/GameWrapper.hpp"
#include "utilities/AssetsManager.hpp"

#include "other/EnemyId.hpp"

#include "systems/SFMLSystem.hpp"

rtype::systems::NetworkSystem::NetworkSystem(const std::string &name)
        : System(name), _serverAddr(), _socket(), _receivePort(8080), _sendPort(6969), _uuid(0), _lobbyId(0)
{
    _socket.setBlocking(false);
}

void rtype::systems::NetworkSystem::onInit()
{
    boost::uuids::random_generator generator;
    boost::uuids::uuid uuid = generator();

    bind();
    std::string uuidString = boost::lexical_cast<std::string>(uuid);
    _uuid = std::strtol(uuidString.substr(0, 8).c_str(), nullptr, 16);
}

void rtype::systems::NetworkSystem::onUpdate([[maybe_unused]] float elapsedTime)
{
    static std::map<rtype::network::RtypeDatagram::RtypeOpCode , void (rtype::systems::NetworkSystem::*)(rtype::network::RtypeDatagram &)> callback = {
            {rtype::network::RtypeDatagram::RtypeOpCodeAvailableLobbies, &rtype::systems::NetworkSystem::handleFetchLobbies},
            {rtype::network::RtypeDatagram::RtypeOpCodeLobbyInfos, &rtype::systems::NetworkSystem::handleLobbyInfo},
            {rtype::network::RtypeDatagram::RtypeOpCodeStartGame, &rtype::systems::NetworkSystem::handleStartGame},
            {rtype::network::RtypeDatagram::RtypeOpCodeUpdateComponents, &rtype::systems::NetworkSystem::handleUpdateComponents},
            {rtype::network::RtypeDatagram::RtypeOpCodeDeletePlayer, &rtype::systems::NetworkSystem::handleDeletePlayer},
            {rtype::network::RtypeDatagram::RtypeOpCodeSpawnEnemy, &rtype::systems::NetworkSystem::handleSpawnEnemy},
            {rtype::network::RtypeDatagram::RtypeOpCodeDeletePlayer, &rtype::systems::NetworkSystem::handleDeletePlayer},
            {rtype::network::RtypeDatagram::RtypeOpCodeEndGame, &rtype::systems::NetworkSystem::handleEndGame}
    };
    if (_serverAddr != sf::IpAddress::None) {
        while (1) {
            rtype::network::Datagram recv = receive();
            if (recv.getSize() == 0)
                break;
            auto rtypeDatagram = *reinterpret_cast<rtype::network::RtypeDatagram *>(&recv);
            auto it = callback.find(rtypeDatagram.getOpCode());
            if (it != callback.end())
                (*this.*(it->second))(rtypeDatagram);
            //INTERPRET recv datagram
        }
    }
}

void rtype::systems::NetworkSystem::onClose()
{
    unbind();
}

void rtype::systems::NetworkSystem::unbind()
{
    _socket.unbind();
}

sf::IpAddress &rtype::systems::NetworkSystem::getServerAddress()
{
    return _serverAddr;
}

sf::UdpSocket &rtype::systems::NetworkSystem::getUdpSocket()
{
    return _socket;
}

unsigned int rtype::systems::NetworkSystem::getSenderPort() const
{
    return _sendPort;
}

unsigned int rtype::systems::NetworkSystem::getReceivePort() const
{
    return _receivePort;
}


void rtype::systems::NetworkSystem::setNewIpAddress(const std::string &newIpAddress)
{
    _serverAddr = sf::IpAddress(newIpAddress);
}

void rtype::systems::NetworkSystem::setSenderPort(unsigned int newPort)
{
    _sendPort = newPort;
}

void rtype::systems::NetworkSystem::setReceivePort(unsigned int newPort)
{
    _receivePort = newPort;
}

void rtype::systems::NetworkSystem::bind()
{
    if (_socket.bind(_receivePort) != sf::Socket::Done) {
        throw NetworkException("Error when binding socket");
    }
}

void rtype::systems::NetworkSystem::send(const rtype::network::Datagram &toSend)
{
    _socket.send(toSend.getData(), toSend.getSize(), _serverAddr, _sendPort);
}

rtype::network::Datagram rtype::systems::NetworkSystem::receive()
{
    sf::IpAddress sender;
    sf::Packet packet;
    sf::Socket::Status status;
    rtype::network::Datagram ret;
    unsigned short port;

    status = _socket.receive(packet, sender, port);
    if (status != sf::Socket::Done)
        return ret;
    ret.setData(packet.getDataSize(), const_cast<void *>(packet.getData()));
    _receivePort = port;
    return ret;
}

uint64_t rtype::systems::NetworkSystem::getUserId() const
{
    return _uuid;
}

void rtype::systems::NetworkSystem::setUserId(uint64_t newUserId)
{
    _uuid = newUserId;
}

uint64_t rtype::systems::NetworkSystem::getLobbyId() const
{
    return _lobbyId;
}

void rtype::systems::NetworkSystem::setLobbyId(uint64_t newLobbyId)
{
    _lobbyId = newLobbyId;
}

void rtype::systems::NetworkSystem::handleFetchLobbies(rtype::network::RtypeDatagram &datagram)
{
    uint32_t nbLobby = 0;
    std::vector<Lobby> lobbies;

    reinterpret_cast<rtype::network::AvailableLobbiesDatagram *>(&datagram)->extractAvailableLobbiesDatagram(nbLobby, lobbies);
    if (rtype::worlds::WorldManager::getInstance().getCurrentWorld()->getWorldName() == "Menu World")
        rtype::worlds::WorldManager::getInstance().changeWorld("Lobby List World");
    dynamic_cast<rtype::worlds::LobbyListWorld *>(rtype::worlds::WorldManager::getInstance().getWorldByName("Lobby List World"))->setNewLobbies(lobbies);
}

void rtype::systems::NetworkSystem::handleLobbyInfo(rtype::network::RtypeDatagram &datagram)
{
    Lobby lobby;

    reinterpret_cast<rtype::network::LobbyInfosDatagram *>(&datagram)->extractLobbyInfosDatagram(lobby);
    _lobbyId = lobby.id;
    if (rtype::worlds::WorldManager::getInstance().getCurrentWorld()->getWorldName() == "Lobby List World")
        rtype::worlds::WorldManager::getInstance().changeWorld("In Lobby World");
    dynamic_cast<rtype::worlds::InLobbyWorld *>(rtype::worlds::WorldManager::getInstance().getWorldByName("In Lobby World"))->setLobby(lobby);
}

void rtype::systems::NetworkSystem::handleStartGame(rtype::network::RtypeDatagram &datagram)
{
    uint32_t componentNumber = 0;
    std::vector<ComponentInfos> components;

    reinterpret_cast<rtype::network::StartGameDatagram *>(&datagram)->extractStartGameDatagram(componentNumber, components);

    dynamic_cast<rtype::worlds::GameWorld *>(rtype::worlds::WorldManager::getInstance().getWorldByName("Game World"))->initGame();
    for (auto &component : components) {
        dynamic_cast<rtype::worlds::GameWorld *>(rtype::worlds::WorldManager::getInstance().getWorldByName("Game World"))->initEntity(component);
    }
    rtype::worlds::WorldManager::getInstance().changeWorld("Game World");
}

void rtype::systems::NetworkSystem::handleDeletePlayer(rtype::network::RtypeDatagram &datagram)
{
    auto &worldManager = rtype::worlds::WorldManager::getInstance();
    auto &gameSettings = rtype::utils::GameSettings::getInstance();
    std::string entityNameToDelete;

    reinterpret_cast<rtype::network::DeletePlayerDatagram *>(&datagram)->extractDeletePlayerDatagram(entityNameToDelete);
    worldManager.getCurrentWorld()->getEntityManager().deleteEntity(entityNameToDelete);
}

void rtype::systems::NetworkSystem::handleUpdateComponents(rtype::network::RtypeDatagram &datagram)
{
    auto &worldManager = rtype::worlds::WorldManager::getInstance();
    auto &gameSettings = rtype::utils::GameSettings::getInstance();
    auto &assetsManager = rtype::utils::AssetsManager::getInstance();
    uint32_t componentNumber = 0;
    std::vector<ComponentInfos> components;

    reinterpret_cast<rtype::network::UpdateComponentsDatagram *>(&datagram)->extractUpdateComponentDatagram(componentNumber, components);
    for (auto &component : components) {
        ecs::entities::Entity *entity = nullptr;

        /* Entity already exists */
        if (worldManager.getCurrentWorld()->getEntityManager().getEntityByName(component.entityName)) {
            entity = worldManager.getCurrentWorld()->getEntityManager().getEntityByName(component.entityName);

            /* Entity doesn't exist and this is not a shoot */
        } else if (!worldManager.getCurrentWorld()->getEntityManager().getEntityByName(component.entityName)) {

            if (std::string(component.entityName).find("shoot") != std::string::npos) {
                dynamic_cast<rtype::worlds::GameWorld *>(worldManager.getCurrentWorld())->shooting(component.entityName);
                entity = worldManager.getCurrentWorld()->getEntityManager().getEntityByName(component.entityName);
            } else {
                worldManager.getCurrentWorld()->getEntityManager().createEntity(component.entityName);
                entity = worldManager.getCurrentWorld()->getEntityManager().getEntityByName(component.entityName);
                entity->assignComponent("Transform", new rtype::components::Transform(*entity));
                entity->assignComponent("Controller", new rtype::components::Controller(*entity, 0));
                entity->assignComponent("Status", new rtype::components::Status(*entity));
            }

        }
        /* Entity doesn't exist and this is a shoot */
        auto transformComponent = dynamic_cast<rtype::components::Transform *>(entity->getComponent("Transform"));
        transformComponent->setPosition(((gameSettings.getWidth() / 3) * component.position.first) / 100, ((gameSettings.getHeight() / 3) * component.position.second) / 100);

        auto controllerComponent = dynamic_cast<rtype::components::Controller *>(entity->getComponent("Controller"));
        controllerComponent->setVelocity(rtype::commons::Vector2<float>(component.velocity.first, component.velocity.second));

        auto statusComponent = dynamic_cast<rtype::components::Status *>(entity->getComponent("Status"));
        statusComponent->setAlive(component.isAlive);
    }
}

void rtype::systems::NetworkSystem::handleEndGame(rtype::network::RtypeDatagram &datagram)
{
    auto &worldManager = rtype::worlds::WorldManager::getInstance();
    auto &gameWrapper = rtype::utils::GameWrapper::getInstance();
    auto sfmlSystem = dynamic_cast<rtype::systems::SFMLSystem *>(gameWrapper.getSystemManager().getSystem("SFML System"));
    EndGameInfos info;

    dynamic_cast<rtype::worlds::GameWorld *>(rtype::worlds::WorldManager::getInstance().getWorldByName("Game World"))->endGame();
    reinterpret_cast<rtype::network::EndGameDatagram *>(&datagram)->extractEndGameDatagram(info);
    sfmlSystem->getWindow().setView(sfmlSystem->getWindow().getDefaultView());
    worldManager.changeWorld("In Lobby World");

    rtype::network::FetchLobbiesDatagram fld;
    fld.createFetchLobbiesDatagram(getUserId());
    send(fld);
}

void rtype::systems::NetworkSystem::handleSpawnEnemy(rtype::network::RtypeDatagram &datagram)
{
    uint64_t enemyId = 0;
    std::pair<float, float> position(0, 0);
    std::string enemyName;

    reinterpret_cast<rtype::network::SpawnEnemyDatagram *>(&datagram)->extractSpawnEnemyDatagram(enemyId, position, enemyName);

    auto &worldManager = rtype::worlds::WorldManager::getInstance();
    auto &assetsManager = rtype::utils::AssetsManager::getInstance();
    auto &gameSettings = rtype::utils::GameSettings::getInstance();

    auto curWorld = worldManager.getCurrentWorld();
    curWorld->getEntityManager().createEntity(enemyName);

    auto entity = curWorld->getEntityManager().getEntityByName(enemyName);
    entity->assignComponent("Transform", new rtype::components::Transform(*entity));
    entity->assignComponent("Controller", new rtype::components::Controller(*entity, 0));
    entity->assignComponent("Status", new rtype::components::Status(*entity));
    entity->assignComponent("Rectangle", new rtype::components::Rectangle(*entity, 0, 0, 32, 32));
    entity->assignComponent("Animator", new rtype::components::Animator(*entity));

    auto animatorComponent = dynamic_cast<rtype::components::Animator *>(entity->getComponent("Animator"));
    animatorComponent->addAnimation("UP", rtype::components::Animator::Animation(3, 4));
    animatorComponent->addAnimation("DOWN", rtype::components::Animator::Animation(1, 0));
    animatorComponent->addAnimation("IDLE", rtype::components::Animator::Animation(2, 2));
    animatorComponent->setCurrentAnimation("IDLE");

    auto transformComponent = dynamic_cast<rtype::components::Transform *>(entity->getComponent("Transform"));
    transformComponent->setPosition(((gameSettings.getWidth() / 3) * position.first) / 100, ((gameSettings.getHeight() / 3) * position.second) / 100);

    switch (enemyId) {
        case ENEMY_ONE:
            entity->assignComponent("Sprite", new rtype::components::Sprite(*entity, assetsManager["enemy_one"]));
            break;
        case ENEMY_TWO:
            entity->assignComponent("Sprite", new rtype::components::Sprite(*entity, assetsManager["enemy_two"]));
            break;
        case ENEMY_THREE:
            entity->assignComponent("Sprite", new rtype::components::Sprite(*entity, assetsManager["enemy_three"]));
            break;
        case ENEMY_FOUR:
            entity->assignComponent("Sprite", new rtype::components::Sprite(*entity, assetsManager["enemy_four"]));
            break;
    }
    auto spriteComponent = dynamic_cast<rtype::components::Sprite *>(entity->getComponent("Sprite"));
    spriteComponent->getSprite().setOrigin(16, 16);
}