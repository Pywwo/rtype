/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** INetworkManager
*/

#ifndef RTYPE_INETWORKMANAGER_HPP
#define RTYPE_INETWORKMANAGER_HPP

#include <string>
#include "network/HostInfos.hpp"
#include "IUdpSocket.hpp"

/*!
 * @namespace rtype
 * @brief Main namespace for all rtype project
 */
namespace rtype {

   /*!
    * @namespace rtype::network
    * @brief Main namespace for all networking
    */
    namespace network {

        /*!
         * @class INetworkManager
         * @brief An interface describing the network manager
         */
        class INetworkManager {
        public:
            /*!
             * @brief Dtor
             */
            virtual ~INetworkManager() = default;

            /*!
             * @brief Start the network manager
             */
            virtual void start(int port) = 0;
            
            /*!
             * @brief Stop the network manager
             */
            virtual void stop() = 0;

            /*!
             * @brief Send datagram through socket
             * @param datagram The datagram to send
             */
            virtual void send(const Datagram &datagram) = 0;

            /*!
             * @brief Receive datagram from socket
             * @return The received datagram
             */
            virtual Datagram receive() = 0;
        };
    }
}

#endif //RTYPE_INETWORKMANAGER_HPP