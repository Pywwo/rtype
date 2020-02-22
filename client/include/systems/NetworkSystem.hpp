
/* Created by Romain FOUYER on 20/11/2019 at 16:24. */


#ifndef RTYPE_NETWORKSYSTEM_HPP
#define RTYPE_NETWORKSYSTEM_HPP

#include <SFML/Network.hpp>

#include "systems/System.hpp"
#include "Datagram.hpp"
#include "RtypeException.hpp"
#include "RtypeDatagram.hpp"

namespace rtype {
    namespace systems {
        /*!
         * @class Network System
         * @brief System to handle network communication
         */
        class NetworkSystem : public ecs::systems::System {
        public:
            explicit NetworkSystem(const std::string &name = "Network System");
            NetworkSystem(const NetworkSystem &other) = delete;
            NetworkSystem &operator=(const NetworkSystem &rhs) = delete;

            void onInit() override;
            void onUpdate(float elapsedTime) override;
            void onClose() override;

            /*!
             * Get the current server address
             *
             * @return the sf::IpAddress
             */
            sf::IpAddress &getServerAddress();

            /*!
             * Get the udp socket
             *
             * @return the udp socket
             */
            sf::UdpSocket &getUdpSocket();

            /*!
             * Set a new ip address to the network system
             *
             * @param newIpAddress the new ip address
             */
            void setNewIpAddress(const std::string &newIpAddress);

            /*!
             * Set a new port to send to the network system
             *
             * @param newPort the new port
             */
            void setSenderPort(unsigned int newPort);
            /*!
             * Return the port where datas are send port of the network system
             *
             * @return the port where datas are send port
             */
            [[nodiscard]] unsigned int getSenderPort() const;
            /*!
             * Return the binded port of the network system
             *
             * @return the binded port
             */
            [[nodiscard]] unsigned int getReceivePort() const;
            /*!
             * Set a new port to receive datas to the network system
             *
             * @param newPort the new port
             */
            void setReceivePort(unsigned int newPort);
            /*!
             * Bind the socket to the receivePort port
             *
             */
            void bind();
            /*!
             * Send a datagram packet to the server
             *
             * @param toSend A datagram to send
             */
            void send(const rtype::network::Datagram &toSend);
            /*!
             * Receive datas. Return empty datagram if no datas or socket non-ready, otherwise a datagram filled with the received datas
             *
             * @return a datagram
             */
            rtype::network::Datagram receive();
            /*!
             * Unbind receivePort. Make the port available
             */
            void unbind();

            /*!
             * Get the user id
             * @return the user id
             */
            [[nodiscard]] uint64_t getUserId() const;

            /*!
             * Set a new user id
             * @param newUserId
             */
            void setUserId(uint64_t newUserId);

            /*!
             * Get the current lobby id
             * @return the current lobby id
             */
            [[nodiscard]] uint64_t getLobbyId() const;

            /*!
             * set a new lobby id
             * @param newLobbyId
             */
            void setLobbyId(uint64_t newLobbyId);
        private:

            /*!
             * @brief function to handle fetch lobbies
             * @param datagram contains all informations about fetch lobbies
             */
            void handleFetchLobbies(rtype::network::RtypeDatagram &datagram);

            /*!
             * @brief function to get lobby info
             * @param datagram contains all informations about the lobby info
             */
            void handleLobbyInfo(rtype::network::RtypeDatagram &datagram);

            /*!
             * @brief function to handle start game
             * @param datagram contains all informations for start the game
             */
            void handleStartGame(rtype::network::RtypeDatagram &datagram);

            /*!
             * @brief function to update components
             * @param datagram contains all informations about the components to update
             */
            void handleUpdateComponents(rtype::network::RtypeDatagram &datagram);

            /*!
             * @brief function to delete player component
             * @param datagram contains all informations about the components to delete
             */
            void handleDeletePlayer(rtype::network::RtypeDatagram &datagram);

            /*!
             * @brief Function to handle the end of the game
             * @param datagram contains information about the end of the game
             */
            void handleEndGame(rtype::network::RtypeDatagram &datagram);

            /*!
             * @brief function who handles the spawn of enemy
             * @param datagram contains all information about the monster who just spawned
             */
            void handleSpawnEnemy(rtype::network::RtypeDatagram &datagram);
        private:
            sf::IpAddress _serverAddr; /*!< contain all hostInfo about the server */
            sf::UdpSocket _socket; /*!< udpSocket to communicate with the server */
            unsigned short _receivePort; /*!< port for receive packet */
            unsigned short _sendPort; /*!< port for send packet */

            uint64_t _uuid; /*!< uid for the userId */
            uint64_t _lobbyId; /*!< contain lobbyId */
        };
    }
}


#endif //RTYPE_NETWORKSYSTEM_HPP
