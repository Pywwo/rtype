
/* Created by Romain FOUYER on 27/11/2019 at 15:31. */

#include <future>
#include "network/datagram/EndGameDatagram.hpp"
#include "network/datagram/LobbyInfosDatagram.hpp"
#include "../include/Game.hpp"

#include "components/Transform.hpp"
#include "components/Timer.hpp"
#include "components/Controller.hpp"
#include "components/Status.hpp"
#include "components/Shoot.hpp"
#include "components/Monster.hpp"
#include "components/BoxCollider.hpp"
#include "components/Damager.hpp"

#include "systems/DLLSystem.hpp"

std::mutex mutex;

const std::map<rtype::network::RtypeDatagram::RtypeOpCode, rtype::network::Game::handleFunc> rtype::network::Game::_opCodeHandleMap = {
        {rtype::network::RtypeDatagram::RtypeOpCodeInput, &Game::handleInputByClient}, // 320
        {rtype::network::RtypeDatagram::RtypeOpCodeLeaveGame, &Game::handleLeaveGame}, // 322
};

rtype::network::Game::Game(const Lobby &lobby, ThreadSafeQueue<Datagram> &datagramQueueOut, std::map<uint64_t, ThreadSafeQueue<RtypeDatagram>> &queueIn, const std::map<uint64_t, HostInfos> &listInfos, GameManager &manager)
: _systemManager(), _entityManager(), _start(true), _lobby(lobby), _datagramQueueOut(datagramQueueOut), _queueIn(queueIn), _listInfos(listInfos), _windowWidth(427), _windowHeight(240), _manager(manager)
{
}

rtype::network::Game::~Game()
{

}

void rtype::network::Game::handleInputByClient(rtype::network::RtypeDatagram &data)
{
    uint64_t userId;
    uint64_t lobbyId;
    RtypeGameKeys key;
    RtypeKeyState state;
    std::string entityName = "player";
    int nbPLayer = 0;

    rtype::network::InputDatagram input = *reinterpret_cast<rtype::network::InputDatagram *>(&data);
    input.extractInputDatagram(userId, lobbyId, key, state);
    for (auto it : _lobby.player) {
        nbPLayer++;
        if (it.id == userId)
            break;
    }
    std::string tmpPlayerName(entityName + std::to_string(nbPLayer));
    auto playerEntity = _entityManager.getEntityByName(tmpPlayerName);
    if (playerEntity == nullptr) {
        // player is dead
        return;
    }
    auto playerController = dynamic_cast<rtype::components::Controller *>(playerEntity->getComponent("Controller"));

    if (state == KEY_PRESSED) {
        switch (key) {
            case KEY_UP:
                playerController->setVelocity(rtype::commons::Vector2<float>(
                    playerController->getVelocity().x,
                    -playerController->getSpeed()
                ));
                break;
            case KEY_LEFT:
                playerController->setVelocity(rtype::commons::Vector2<float>(
                    -playerController->getSpeed(),
                    playerController->getVelocity().y
                ));
                break;
            case KEY_RIGHT:
                playerController->setVelocity(rtype::commons::Vector2<float>(
                    playerController->getSpeed(),
                    playerController->getVelocity().y
                ));
                break;
            case KEY_DOWN:
                playerController->setVelocity(rtype::commons::Vector2<float>(
                    playerController->getVelocity().x,
                    playerController->getSpeed()
                ));
                break;
            case KEY_SHOOT:

                break;
            default: break;
        }
    } else if (state == KEY_RELEASED) {
        switch (key) {
            case KEY_UP:
                playerController->setVelocity(rtype::commons::Vector2<float>(
                    playerController->getVelocity().x,
                    0
                ));
                break;
            case KEY_LEFT:
                playerController->setVelocity(rtype::commons::Vector2<float>(
                    0,
                    playerController->getVelocity().y
                ));
                break;
            case KEY_RIGHT:
                playerController->setVelocity(rtype::commons::Vector2<float>(
                    0,
                    playerController->getVelocity().y
                ));
                break;
            case KEY_DOWN:
                playerController->setVelocity(rtype::commons::Vector2<float>(
                    playerController->getVelocity().x,
                    0
                ));
                break;
            case KEY_SHOOT:
                handleShoot(tmpPlayerName);
                break;
            default: break;
        }
    }
    //update system by the collected info
    sendUpdatePosition();
    sendUpdateShoot();
}

void rtype::network::Game::handleShoot(const std::string &entityPlayerName)
{
    static long nbShoot = 1;
    std::string nameShoot = "shoot";

    // get info transfrom about the player
    auto playerEntity = _entityManager.getEntityByName(entityPlayerName);
    auto playerTransform = dynamic_cast<rtype::components::Transform *>(playerEntity->getComponent("Transform"));

    // assign component to shoot
    std::string tmpShoot(nameShoot + std::to_string(nbShoot));
    _entityManager.createEntity(tmpShoot);
    auto shootEntity = _entityManager.getEntityByName(tmpShoot);
    shootEntity->assignComponent("Transform", new rtype::components::Transform(*shootEntity));
    shootEntity->assignComponent("Controller", new rtype::components::Controller(*shootEntity, 200));
    shootEntity->assignComponent("Timer", new rtype::components::Timer(*shootEntity, 1));
    shootEntity->assignComponent("Shoot", new rtype::components::Shoot(*shootEntity));
    shootEntity->assignComponent("BoxCollider", new rtype::components::BoxCollider(*shootEntity, rtype::commons::Vector2<float>{2, 2}));
    shootEntity->assignComponent("Damager", new rtype::components::Damager(*shootEntity, *playerEntity, true));

    auto shootController = dynamic_cast<rtype::components::Controller *>(shootEntity->getComponent("Controller"));
    shootController->setVelocity(rtype::commons::Vector2<float>(shootController->getSpeed(), 0));

    auto shootTransform = dynamic_cast<rtype::components::Transform *>(shootEntity->getComponent("Transform"));
    shootTransform->setPosition(playerTransform->getPosition().x + 64, playerTransform->getPosition().y);
    nbShoot++;
}

void rtype::network::Game::sendDeletePlayer(const std::string &playerName)
{
    for (auto it : _lobby.player) {
        if (it.id != 0) {
            Datagram datagram(_listInfos[it.id]);
            reinterpret_cast<rtype::network::DeletePlayerDatagram *>(&datagram)->createDeletePlayerDatagram(playerName);
            _datagramQueueOut.push_back(datagram);
        }
    }
}

void rtype::network::Game::handleLeaveGame(rtype::network::RtypeDatagram &data)
{
    uint64_t userId;
    uint64_t lobbyId;
    int nbPlayer = 0;
    int nbPlayerToDelete = 0;
    std::string playerToDelete("player");

    rtype::network::LeaveGameDatagram input = *reinterpret_cast<rtype::network::LeaveGameDatagram *>(&data);
    input.extractLeaveGameDatagram(userId, lobbyId);
    for (auto &it : _lobby.player) {
        nbPlayerToDelete++;
        if (it.id != 0 && it.id == userId) {
            it.id = 0;
            playerToDelete += std::to_string(nbPlayerToDelete);
        }
    }
    for (auto &it : _lobby.player)
        if (it.id != 0)
            nbPlayer++;
    if (nbPlayer == 0) {
        _start = false;
        _lobby.id = 0;
        return;
    }
    _entityManager.deleteEntity(playerToDelete);
    sendDeletePlayer(playerToDelete);
}

void rtype::network::Game::manageReceivedDatagram()
{
    RtypeDatagram firstElement;

    firstElement = _queueIn[_lobby.id].front();
    try {
        (*this.*(_opCodeHandleMap.at(firstElement.getOpCode())))(firstElement);
    } catch (const std::out_of_range &err) {
        return;
    }
    _queueIn[_lobby.id].pop();
}

ecs::managers::SystemManager& rtype::network::Game::getSystemManager()
{
    return _systemManager;
}

ecs::managers::EntityManager& rtype::network::Game::getEntityManager()
{
    return _entityManager;
}

void rtype::network::Game::initPlayer()
{
    int nbPlayer = 0;
    float posY = 0;
    int nbAllplayers = 0;
    std::string playerName = "player";

    for (auto it : _lobby.player) {
        if (it.id != 0) {
            nbAllplayers++;
        }
    }
    float posToAdd = _windowHeight / (nbAllplayers + 1);
    posY = _windowHeight / (nbAllplayers + 1);
    for (auto it : _lobby.player) {
        nbPlayer++;
        if (it.id != 0) {
            std::string tmpPlayerName(playerName + std::to_string(nbPlayer));
            _entityManager.createEntity(tmpPlayerName);
            auto playerEntity = _entityManager.getEntityByName(tmpPlayerName);
            playerEntity->assignComponent("Transform", new rtype::components::Transform(*playerEntity));
            playerEntity->assignComponent("Controller", new rtype::components::Controller(*playerEntity, 100));
            playerEntity->assignComponent("Status", new rtype::components::Status(*playerEntity));
            playerEntity->assignComponent("BoxCollider", new rtype::components::BoxCollider(*playerEntity, rtype::commons::Vector2<float>{32, 32}));
            auto playerTransform = dynamic_cast<rtype::components::Transform *>(playerEntity->getComponent("Transform"));
            playerTransform->setPosition(50, posY);
            std::cout << posY << std::endl;
            posY += posToAdd;
        }
    }
}

void rtype::network::Game::startGame()
{
    int nbPlayer = 0;
    std::string playerName = "player";
    uint32_t nbComponents = 0;
    std::vector<ComponentInfos> components;

    for (auto it : _lobby.player) {
        nbPlayer++;
        if (it.id != 0) {
            ComponentInfos infos;
            std::string tmpPlayerName(playerName + std::to_string(nbPlayer));
            auto playerEntity = _entityManager.getEntityByName(tmpPlayerName);
            auto playerTransform = dynamic_cast<rtype::components::Transform *>(playerEntity->getComponent("Transform"));
            std::strcpy(infos.entityName, tmpPlayerName.c_str());
            infos.position.first = (playerTransform->getPosition().x * 100) / _windowWidth;
            infos.position.second = (playerTransform->getPosition().y * 100) / _windowHeight;
            infos.velocity = std::pair<float, float>(0, 0);
            components.push_back(infos);
            nbComponents++;
        }
    }
    for (auto it : _lobby.player) {
        if (it.id != 0) {
            Datagram datagram(_listInfos[it.id]);
            reinterpret_cast<rtype::network::StartGameDatagram *>(&datagram)->createStartGameDatagram(nbComponents, components);
            _datagramQueueOut.push_back(datagram);
        }
    }
}

void rtype::network::Game::sendUpdatePosition()
{
    std::vector<ComponentInfos> components;
    std::vector<std::string> componentsNameToGet = {"Transform", "Controller", "Status"};
    std::vector<ecs::entities::Entity *> allEntity = _entityManager.getEntitiesWithComponents(componentsNameToGet);
    uint32_t nbComponents = 0;

    for (auto &it : allEntity) {
        ComponentInfos info;

        auto playerTransform = dynamic_cast<rtype::components::Transform *>(it->getComponent("Transform"));
        auto playerController = dynamic_cast<rtype::components::Controller *>(it->getComponent("Controller"));
        auto playerStatus = dynamic_cast<rtype::components::Status *>(it->getComponent("Status"));

        std::strcpy(info.entityName, it->getName().c_str());
        info.position.first = (playerTransform->getPosition().x * 100) / _windowWidth;
        info.position.second = (playerTransform->getPosition().y * 100) / _windowHeight;

        info.velocity = std::make_pair(playerController->getVelocity().x, playerController->getVelocity().y);
        info.isAlive = playerStatus->isAlive();
        components.push_back(info);
        nbComponents++;
    }
    for (auto it : _lobby.player) {
        if (it.id != 0) {
            Datagram datagram(_listInfos[it.id]);
            reinterpret_cast<rtype::network::UpdateComponentsDatagram *>(&datagram)->createUpdateComponentDatagram(nbComponents, components);
            _datagramQueueOut.push_back(datagram);
        }
    }
}

void rtype::network::Game::sendUpdateShoot()
{
    std::vector<ComponentInfos> components;
    std::vector<std::string> componentsNameToGet = {"Shoot"};
    std::vector<ecs::entities::Entity *> allShootEntity = _entityManager.getEntitiesWithComponents(componentsNameToGet);
    uint32_t nbComponents = 0;

    for (auto &it : allShootEntity) {
        ComponentInfos info;

        auto shootTransform = dynamic_cast<rtype::components::Transform *>(it->getComponent("Transform"));
        auto shootController = dynamic_cast<rtype::components::Controller *>(it->getComponent("Controller"));

        std::strcpy(info.entityName, it->getName().c_str());
        info.position.first = (shootTransform->getPosition().x * 100) / _windowWidth;
        info.position.second = (shootTransform->getPosition().y * 100) / _windowHeight;

        info.velocity = std::make_pair(shootController->getVelocity().x, shootController->getVelocity().y);
        info.isAlive = true;
        components.push_back(info);
        nbComponents++;
    }
    if (nbComponents == 0)
        return;
    for (auto it : _lobby.player) {
        if (it.id != 0) {
            Datagram datagram(_listInfos[it.id]);
            reinterpret_cast<rtype::network::UpdateComponentsDatagram *>(&datagram)->createUpdateComponentDatagram(nbComponents, components);
            _datagramQueueOut.push_back(datagram);
        }
    }
}

void rtype::network::Game::sendUpdateEnemy()
{
    std::vector<ComponentInfos> components;
    std::vector<std::string> componentsMonsterToGet = {"Monster"};
    std::vector<ecs::entities::Entity *> allMonsterEntity = _entityManager.getEntitiesWithComponents(componentsMonsterToGet);
    uint32_t nbComponents = 0;

    for (auto &it : allMonsterEntity) {
        if (dynamic_cast<rtype::components::Monster *>(it->getComponent("Monster"))->isSpawned() == false) {
            auto enemyTransform = dynamic_cast<rtype::components::Transform *>(it->getComponent("Transform"));
            uint64_t enemyType = dynamic_cast<rtype::components::Monster *>(it->getComponent("Monster"))->getId();
            for (auto jt : _lobby.player) {
                if (jt.id != 0) {
                    rtype::network::Datagram datagram(_listInfos.at(jt.id));
                    reinterpret_cast<rtype::network::SpawnEnemyDatagram *>(&datagram)->createSpawnEnemyDatagram(enemyType, std::make_pair(enemyTransform->getPosition().x, enemyTransform->getPosition().y), it->getName());
                    _datagramQueueOut.push_back(datagram);
                }
            }
            //set spawn state
            dynamic_cast<rtype::components::Monster *>(it->getComponent("Monster"))->setSpawnState(true);
        } else {
            ComponentInfos info;

            auto playerTransform = dynamic_cast<rtype::components::Transform *>(it->getComponent("Transform"));
            auto playerController = dynamic_cast<rtype::components::Controller *>(it->getComponent("Controller"));
            auto playerStatus = dynamic_cast<rtype::components::Status *>(it->getComponent("Status"));

            std::strcpy(info.entityName, it->getName().c_str());
            info.position.first = (playerTransform->getPosition().x * 100) / _windowWidth;
            info.position.second = (playerTransform->getPosition().y * 100) / _windowHeight;

            info.velocity = std::make_pair(playerController->getVelocity().x, playerController->getVelocity().y);
            info.isAlive = playerStatus->isAlive();
            components.push_back(info);
            nbComponents++;
        }
    }
    for (auto it : _lobby.player) {
        if (it.id != 0) {
            Datagram datagram(_listInfos[it.id]);
            reinterpret_cast<rtype::network::UpdateComponentsDatagram *>(&datagram)->createUpdateComponentDatagram(nbComponents, components);
            _datagramQueueOut.push_back(datagram);
        }
    }
}

bool rtype::network::Game::checkIfGameEnd()
{
    int playerAlive = 0;

    for (auto &it : _entityManager.getEntitiesWithComponents(std::vector<std::string>({"Transform"}))) {
        if (it->getName().find("player") != std::string::npos)
            playerAlive++;
    }
    return playerAlive == 0;
}

void rtype::network::Game::run()
{
    // Create new Systems
    _systemManager.newSystem("DLL system", new rtype::systems::DLLSystem("DLL system", _systemManager, _entityManager));

    // Start all systems created before
    _systemManager.startSystem("DLL system");

    initPlayer();
    startGame();

    // main loop game
    float time = 0;
    while (_start) {
        if (!_queueIn[_lobby.id].isEmpty()) {
            manageReceivedDatagram();
        }
        if (time > 0.5) {
            sendUpdateShoot();
            sendUpdateEnemy();
            sendUpdatePosition();
            time = 0;
        }

        if (checkIfGameEnd()) {
            for (auto it : _lobby.player) {
                if (it.id != 0) {
                    Datagram datagram(_listInfos[it.id]);
                    reinterpret_cast<rtype::network::EndGameDatagram *>(&datagram)->createEndGameDatagram({0});
                    _datagramQueueOut.push_back(datagram);
                }
            }
            _start = false;
        }

        _systemManager.runningTime();
        time += _systemManager.getElapsedTime() / 1000000000.0f;
    }
     // Stop all systems
    _systemManager.stopSystem("DLL system");
    std::async([=](std::thread::id id) {
        std::lock_guard<std::mutex> lock(mutex);
        _manager.handleEndGame(id, _lobby);
    }, std::this_thread::get_id());
}