/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** RtypeServer
*/

#ifndef RTYPE_RTYPESERVER_HPP
#define RTYPE_RTYPESERVER_HPP

#include <map>
#include <regex>
#include <thread>
#include <iostream>
#include <csignal>
#include <chrono>

#include "NetworkManager.hpp"
#include "RtypeDatagram.hpp"
#include "AvailableLobbiesDatagram.hpp"
#include "CreateLobbyDatagram.hpp"
#include "FetchLobbiesDatagram.hpp"
#include "EndGameDatagram.hpp"
#include "InputDatagram.hpp"
#include "LobbyInfosDatagram.hpp"
#include "ConnectLobbyDatagram.hpp"
#include "LeaveLobbyDatagram.hpp"
#include "StartGameDatagram.hpp"
#include "PlayerDeathDatagram.hpp"
#include "TriggerBonusDatagram.hpp"
#include "RequestStartGameDatagram.hpp"
#include "SpawnEnemyDatagram.hpp"
#include "EnemyDeathDatagram.hpp"
#include "UpdateComponentsDatagram.hpp"
#include "BinaryDatagram.hpp"
#include "IUdpSocket.hpp"
#include "UdpSocket.hpp"
#include "GameManager.hpp"
#include "LeaveGameDatagram.hpp"

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

        /*!
         * @class RtypeServer
         * @brief Main rtype server class
         */ 
        class RtypeServer {
        public:
            /*!
             * @brief ctor
             */
            RtypeServer();

            /*!
             * @brief dtor
             */ 
            ~RtypeServer() = default;

            /*!
             * @brief run the server and bind a port
             * @param port the bind port for rtype server
             */
            void run(int port);

            /*!
             * @brief stop the rtype server
             */
            void stop();

            /*!
             * @brief set the TimeVal for change the speed handling packet of the rtype server
             */ 
            void setTimeVal(const unsigned int &newTimeVal);

           /*!
             * @brief get the current TimeVal of the rtype server
             */ 
            [[nodiscard]] unsigned int getTimeVal() const;

        private:

            /*!
             * @brief receive data from all player's
             */
            void receive();

            /*!
             * @brief function for handle the connection player to the rtype server
             */ 
            void handleConnection();

            /*!
             * @brief function for handle the disconnection player to the rtype server
             */
            void handleDisconnection();

            /*!
             * @brief Take first datagram inside out queue and retrieve it
             */
            void sendFirstDatagramInQueue();

        private:

            /*!
             * @brief handle datagram connect server 120
             * @param data RtypeDatagram sent
             */
            void handleConnectServer(RtypeDatagram &data);
            /*!
             * @brief handle datagram create lobby 220
             * @param data RtypeDatagram sent
             */ 
            void handleCreateLobby(RtypeDatagram &data);

            /*!
             * @brief handle datagram fetch lobbies 221
             * @param data RtypeDatagram sent
             */ 
            void handleFetchLobbies(RtypeDatagram &data);

            /*!
             * @brief handle datagram key pressed 320
             * @param data RtypeDatagram sent
             */ 
            void handleInput(RtypeDatagram &data);

            /*!
             * @brief handle datagram binary code 100
             * @param data RtypeDatagram sent
             */ 
            void handleCodeBinary(RtypeDatagram &data);

            /*!
             * @brief handle datagram binary code 321
             * @param data RtypeDatagram sent
             */
            void handleRequestStartGame(RtypeDatagram &data);

            /*!
             * @brief handle datagram connect lobby 222
             * @param data RtypeDatagram sent
             */ 
            void handleConnectLobby(RtypeDatagram &data);

            /*!
             * @brief handle datagram leave lobby 223
             * @param data RtypeDatagram sent
             */
            void handleLeaveLobby(RtypeDatagram &data);

            /*!
             * @brief handle datagram leave game 322
             * @param data RtypeDatagram sent
             */
            void handleLeaveGame(RtypeDatagram &data);

            /*!
             * @brief send error to client if an internal error occurred
             * @param hostInfos The client host infos
             * @param error The error message
             */
            void sendError(const HostInfos &hostInfos, const std::string &error) const;

        private:
            /*!
             * @brief Catch the signal in the rtype server
             */
            static void SignalHandler(int signal);

            static bool caughtSigInt; /*!< static variable that check if a sigInt was caught */

        private:
            /*!
             * @brief typedef for all handleFunc
             * @param data RtypeDatagram sent to the rtypeServer
             */ 
            typedef void (RtypeServer::*handleFunc)(RtypeDatagram &datagram); /*!< handle function with datagram in param */ 

            static const std::map<RtypeDatagram::RtypeOpCode, handleFunc> _opCodeHandleMap; /*!< Map for call the good function for each datagramOpCode */

        private:
            std::unique_ptr<INetworkManager> _networkManager; /*!< The network manager of the rtype server */
            bool _isStarted; /*!< Is the rtype server is started */
            unsigned int _timeVal; /*!< Handle the speed of the server of handling receive and send */
            GameManager &_manager; /*!< Handle the gameManager */
            std::map<uint64_t, HostInfos> _clientHosts; /*!< The list of client/host bindings */
        };

    }
}

#endif // RTYPE_RTYPESERVER_HPP