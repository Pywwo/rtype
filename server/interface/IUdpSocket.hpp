/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** IUdpSocket
*/

#ifndef RTYPE_IUDPSOCKET_HPP
#define RTYPE_IUDPSOCKET_HPP

#include "network/HostInfos.hpp"
#include "network/datagram/Datagram.hpp"

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
         * @class IUdpSocket
         * @brief An interface describing the udp socket
         */
        class IUdpSocket {
        public:
            /*!
             * @brief Dtor
             */
            virtual ~IUdpSocket() = default;

            /*!
             * @brief Bind this socket to a port
             * @param port The port to bind to
             */
            virtual void bind(int port) = 0;

            /*!
             * @brief Unbind this socket from the port it was binded to
             */
            virtual void unbind() = 0;

            /*!
             * @brief Send raw data from this socket
             * @param data The data to send
             */
            virtual void send(const Datagram &datagram) = 0;

            /*!
             * @brief Get the bind port
             * @return -1 if no port has been bind or the port
             */
            virtual int getPort() const = 0;

            /*!
             * @brief Get the address of this socket
             * @return the address of this socket
             */
            virtual std::string getAddress() const = 0;
        };
    }
}

#endif //RTYPE_IUDPSOCKET_HPP