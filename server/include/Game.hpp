
/* Created by Romain FOUYER on 27/11/2019 at 15:31. */


#ifndef RTYPE_GAME_HPP
#define RTYPE_GAME_HPP

#include "entities/EntityManager.hpp"
#include "systems/SystemManager.hpp"
#include "other/Lobby.hpp"
#include "ThreadSafeQueue.hpp"
#include "Datagram.hpp"
#include "RtypeDatagram.hpp"
#include "LeaveGameDatagram.hpp"
#include "InputDatagram.hpp"
#include "other/ComponentInfos.hpp"
#include "StartGameDatagram.hpp"
#include <cstring>
#include "UpdateComponentsDatagram.hpp"
#include "DeletePlayerDatagram.hpp"
#include "GameManager.hpp"
#include "SpawnEnemyDatagram.hpp"

/*!
 * @namespace rtype
 * @brief Main namespace for all project
 */
namespace rtype {

    /*!
     * @brief rtype::network
     * @brief Main namespace for all networking
     */
    namespace network {

        /*!
         * @class Game
         * @brief handle all game for server
         */
        class Game {
        public:
            /*!
             * @brief ctor
             */
            explicit Game(const Lobby &lobby, ThreadSafeQueue<Datagram> &datagramQueueOut, std::map<uint64_t, ThreadSafeQueue<RtypeDatagram>> &queueIn, const std::map<uint64_t, HostInfos> &listInfos, GameManager &manager);

            /*!
             * @brief dtor
             */
            ~Game();

            /*!
             * @brief function for run the game
             */
            void run();

            ecs::managers::SystemManager &getSystemManager();
            ecs::managers::EntityManager &getEntityManager();
        private:
            /*!
             * @brief function for handle all input of the client
             * @param data Datagram for input
             */
            void handleInputByClient(RtypeDatagram &data);

            /*!
             * @brief function for handle if a client leave the game
             * @param data Datagram for leave the game
             */
            void handleLeaveGame(RtypeDatagram &data);

            /*!
             * @brief function for manage all received Datagram
             */
            void manageReceivedDatagram();

            /*!
             * @brief function for init all player in the game
             */
            void initPlayer();

            /*!
             * @brief function for handle the start game
             */
            void startGame();

            /*!
             * @brief function for handle the shooting
             */
            void handleShoot(const std::string &entityPlayerName);

            /*!
             * @brief function to send to all clients the updated position
             */
            void sendUpdatePosition();

            /*!
             * @brief function for update shoot
             */
            void sendUpdateShoot();

            /*!
             * @brief send to all active client that a player is deleted
             */
            void sendDeletePlayer(const std::string &playerName);

            /*!
             * @brief function for update enemy
             */
            void sendUpdateEnemy();

            bool checkIfGameEnd();
        private:
            ecs::managers::SystemManager _systemManager; /*!< Handle all system */
            ecs::managers::EntityManager _entityManager; /*!< handle all entity */

            bool _start; /*!< If the rtype server is started true otherwise false */

            Lobby _lobby; /*!< handle all lobby */
            ThreadSafeQueue<Datagram> &_datagramQueueOut; /*!< handle all datagram out thread safe */
            std::map<uint64_t, ThreadSafeQueue<RtypeDatagram>> &_queueIn; /*!< handle all datagram in thread safe */
            std::map<uint64_t, HostInfos> _listInfos; /*!< The list of all client id with hostInfo of each client */

        private:
            typedef void (Game::*handleFunc)(RtypeDatagram &datagram); /*!< handle function with datagram in param */
            static const std::map<RtypeDatagram::RtypeOpCode, handleFunc> _opCodeHandleMap; /*!< Map for call the good function for each datagramOpCode */

            int _windowWidth; /*!< handle the window width */
            int _windowHeight; /*!< handle the window height */

            GameManager &_manager;
        };
    }
}


#endif //RTYPE_GAME_HPP
