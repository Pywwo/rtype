/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** gameManager
*/

#include "GameManager.hpp"

#include "Game.hpp"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <iostream>
#include "exception/RtypeException.hpp"

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

    #include <bcrypt.h>
    #pragma comment(lib, "bcrypt.lib")

#endif

rtype::network::GameManager::GameManager()
    : _playerLobby(), _mutex(), _workers(), _lobbies()
{

}

rtype::network::GameManager::~GameManager()
{

}

void rtype::network::GameManager::joinLobby(uint64_t playerId, uint64_t lobbyId)
{
    auto it = std::find_if(_playerLobby.begin(), _playerLobby.end(),
                           [&playerId](const std::pair<uint64_t, uint64_t> &elem) {
                               return playerId == elem.first;
                           });
    if (it != _playerLobby.end() && it->second != 0) {
        throw AlreadyInLobbyException("You're already member of a lobby");
    }
    try {
        for (auto &player : _lobbies.at(lobbyId).player) {
            if (player.id == 0) {
                player.id = playerId;
                it = std::find_if(_playerLobby.begin(), _playerLobby.end(),
                        [&playerId](const std::pair<uint64_t, uint64_t> &elem) {
                    return playerId == elem.first;
                });
                if (it == _playerLobby.end()) {
                    _playerLobby.emplace_back(std::make_pair(playerId, lobbyId));
                } else {
                    (*it).second = lobbyId;
                }
                return;
            }
        }
    } catch (std::out_of_range &e) {
        throw NonExistentLobbyException("Required lobby does not exist");
    }
    throw LobbyFullException("Required lobby is already full");
}

uint64_t rtype::network::GameManager::createLobby(uint64_t playerId)
{
    boost::uuids::random_generator generator;
    boost::uuids::uuid uuid = generator();

    std::string uuidString = boost::lexical_cast<std::string>(uuid);
    uint64_t lobbyId = std::strtoull(uuidString.c_str(), nullptr, 16);
    auto it = std::find_if(_playerLobby.begin(), _playerLobby.end(),
    [&playerId](const std::pair<uint64_t, uint64_t> &element) {
        return element.first == playerId;
    });
    if (it == _playerLobby.end()) {
        _playerLobby.emplace_back(std::make_pair(playerId, lobbyId));        
    } else {
        (*it).second = lobbyId;
    }
    Lobby lobby = {
            lobbyId,
            {
                    {playerId, "player1"},
                    {0, "player2"},
                    {0, "player3"},
                    {0, "player4"}
            }
    };
    _lobbies.emplace(std::make_pair(lobbyId, lobby));
    return lobbyId;
}

std::vector<rtype::Lobby> rtype::network::GameManager::getAvailableLobbies() const
{
    std::vector<Lobby> availableLobbies;

    for (auto &lobby : _lobbies) {
        availableLobbies.push_back(lobby.second);
    }
    return availableLobbies;
}

void rtype::network::GameManager::leaveLobby(uint64_t playerId, uint64_t lobbyId)
{
    auto it = std::find_if(_playerLobby.begin(), _playerLobby.end(),
    [&playerId](const std::pair<uint64_t, uint64_t> &element) {
        return element.first == playerId;
    });
    if (it == _playerLobby.end()) {
        throw NotInLobbyException("You can't leave a lobby you're not part of");
    } else {
        (*it).second = 0;
    }
    int nbPlayers = 0;
    try {
        for (auto &player : _lobbies.at(lobbyId).player) {
            if (player.id == playerId) {
                player.id = 0;
            } else if (player.id != 0) {
                nbPlayers++;
            }
        }
    } catch (std::out_of_range &e) {
        throw NonExistentLobbyException("Required lobby does not exist");
    }
    if (nbPlayers == 0) {
        _lobbies.erase(lobbyId);
    }
}

rtype::Lobby rtype::network::GameManager::getLobby(uint64_t lobbyId) const
{
    try {
        return _lobbies.at(lobbyId);
    } catch (std::out_of_range &e) {
        throw NonExistentLobbyException("Required lobby does not exist");
    }
}

uint64_t rtype::network::GameManager::getLobbyId(uint64_t playerId) const
{
    auto player = std::find_if(_playerLobby.begin(), _playerLobby.end(),
            [&playerId](const std::pair<uint64_t, uint64_t> &elem) {
        return elem.first == playerId;
    });
    return (*player).second;
}

void rtype::network::GameManager::handleStartGame(uint64_t lobbyId,  const std::map<uint64_t, HostInfos> &listInfos)
{
    Lobby gameLobby = getLobby(lobbyId);

    std::thread newGameThread(&runGame, gameLobby, std::ref(_datagramQueueOut), std::ref(_queueIn), listInfos, std::ref(*this));
    _workers.push_back(std::move(newGameThread));
    _lobbies.erase(lobbyId);
}

void rtype::network::GameManager::handleEndGame(std::thread::id id, const Lobby &lobby)
{
    auto it = std::find_if(_workers.begin(), _workers.end(), [=](std::thread &thread) {
        return thread.get_id() == id;
    });
    if (it != _workers.end()) {
        _lobbies.emplace(std::pair<uint64_t, Lobby>(lobby.id, lobby));
        _queueIn.erase(lobby.id);
        it->detach();
        _workers.erase(it);
    }
}

void rtype::network::GameManager::runGame(const Lobby &gameLobby, ThreadSafeQueue<Datagram> &datagramQueueOut, std::map<uint64_t, ThreadSafeQueue<RtypeDatagram>> &queueIn, const std::map<uint64_t, HostInfos> &listInfos, GameManager &manager)
{
    rtype::network::Game game(gameLobby, datagramQueueOut, queueIn, listInfos, manager);

    game.run();
}

rtype::network::GameManager &rtype::network::GameManager::getGameManagerInstance()
{
    static GameManager gameManager;

    return gameManager;
}

bool rtype::network::GameManager::hasPendingDatagram()
{
    return !_datagramQueueOut.isEmpty();
}

rtype::network::Datagram rtype::network::GameManager::getFirstElementInQueue()
{
   return _datagramQueueOut.front();
}

void rtype::network::GameManager::popFirstElementInQueue()
{
    _datagramQueueOut.pop();
}

void rtype::network::GameManager::pushDatagramByLobby(uint64_t lobbyId, RtypeDatagram &data)
{
    _queueIn.at(lobbyId).push_back(data);
}