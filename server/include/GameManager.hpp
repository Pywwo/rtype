/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** GameManager
*/

#ifndef RTYPE_GAMEMANAGER_HPP
#define RTYPE_GAMEMANAGER_HPP

#include <vector>
#include <mutex>
#include <iostream>
#include <string>
#include <queue>
#include <thread>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <map>

#include "other/Lobby.hpp"
#include "systems/SystemManager.hpp"
#include "RequestStartGameDatagram.hpp"
#include "StartGameDatagram.hpp"
#include "Datagram.hpp"
#include "ThreadSafeQueue.hpp"
#include "entities/EntityManager.hpp"

/*!
 * @namespace rtype
 * @brief Main namespace for all project
 */
namespace rtype {

    /*!
     * @namespace rtype::network
     * @brief Main namespace for all networking
     */
    namespace network {
        class GameManager {
        private:

            /*!
             * @brief ctor
             */
            GameManager();

        public:
        
            /*!
             * @brief dtor
             */
            ~GameManager();

            /*!
             * @brief function for create a new lobby
             * @param playerId player id created the lobby
             * @return uint64_t lobbyId created
             */
            uint64_t createLobby(uint64_t playerId);

            /*!
             * @brief function to join a lobby
             * @param playerId player id of the player wanting to join lobby
             * @param lobbyId lobby id to join
             */
            void joinLobby(uint64_t playerId, uint64_t lobbyId);

            /*!
             * @brief function to get all available lobbies
             * @return vecotr<Looby> all the lobby available
             */
            [[nodiscard]] std::vector<Lobby> getAvailableLobbies() const;

            /*!
             * @brief function to leave a lobby
             * @param playerId player id of the player leaving the lobby
             * @param lobbyId lobby id
             */
            void leaveLobby(uint64_t playerId, uint64_t lobbyId);

            /*!
             * @brief function to get a specific lobby
             * @param lobbyId lobby id that u want to get
             * @return Lobby all info about the lobby
             */
            [[nodiscard]] Lobby getLobby(uint64_t lobbyId) const;

            /*!
             * @brief function to get the id lobby where the player is
             * @param playerId player id that u want to get
             * @return Lobby the lobby where the player is
             */
            [[nodiscard]] uint64_t getLobbyId(uint64_t playerId) const;

            /*!
             * @brief function for handle all thread started game
             * @param lobbyId lobby id that u want to start
             * @param listInfos the map of the game's user id and their corresponding hostinfos
             */
            void handleStartGame(uint64_t lobbyId,  const std::map<uint64_t, HostInfos> &listInfos);

            void handleEndGame(std::thread::id id, const Lobby &lobby);

            GameManager(const GameManager&) = delete;
            GameManager &operator=(const GameManager&) = delete;

            /*!
            * @brief Function for get the parser instance
            * @return the parsingProtocol instance
            */
            static GameManager &getGameManagerInstance();

            /*!
            * @brief Function to know if queueOut has pending datagram
            * @return bool true if queueOut has pending datagram
            */
            bool hasPendingDatagram();

            /*!
            * @brief Function get the first element in queue Out
            * @return Datagram the first element in queue out
            */
            [[nodiscard]] Datagram getFirstElementInQueue();

            /*!
            * @brief Pop the first element in queue out
            */
            void popFirstElementInQueue();

            /*!
            * @brief push a datagram in queueIn by the lobby id
            */
            void pushDatagramByLobby(uint64_t lobbyId, RtypeDatagram &data);

            private:
            /*!
             * @brief thread function to run the game
             */
            static void runGame(const Lobby &gameLobby, ThreadSafeQueue<Datagram> &datagramQueueOut, std::map<uint64_t, ThreadSafeQueue<RtypeDatagram>> &queueIn, const std::map<uint64_t, HostInfos> &listInfos, GameManager &manager);

        private:
            std::vector<std::pair<uint64_t, uint64_t>> _playerLobby; /*!< handle player id first and lobby id secondly */
            std::mutex _mutex; /*!< handle lock thread */
            std::vector<std::thread> _workers; /*!< worker for handle all the thread */
            std::map<uint64_t, Lobby> _lobbies; /*!< map of lobbies by player id */
            ThreadSafeQueue<Datagram> _datagramQueueOut; /*!< queue out to handle all game datagram in the thread function */
            std::map<uint64_t, ThreadSafeQueue<RtypeDatagram>> _queueIn; /*< queue in by lobby id */
        };
    }
}

#endif // RTYPE_GAMEMANAGER_HPP