/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** ConnectServerDatagram.hpp
*/

/* Created the 27/11/2019 at 15:43 by jbulteau */

#ifndef RTYPE_CONNECTSERVERDATAGRAM_HPP
#define RTYPE_CONNECTSERVERDATAGRAM_HPP

#include "RtypeDatagram.hpp"

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
         * @class ConnectServerDatagram
         * @brief Datagram for initial command
         */
        class ConnectServerDatagram : public RtypeDatagram {
        public:
            /*!
             * @brief ctor
             */
             ConnectServerDatagram() = default;
             /*!
              * @brief dtor
              */
              ~ConnectServerDatagram() = default;

              /*!
               * @brief Create datagram for connect server command
               * @param userId The user id
               * @param port The port where the client will listen to the server
               */
               void createConnectServerDatagram(uint64_t userId, int port);
               /*!
                * @brief Extract host's data from the datagram
                * @param userId The user id filled with datagram content
                * @param hostInfos The port of the client filled with datagram's content
                */
                void extractConnectServerDatagram(uint64_t &userId, int &port);
        };
    }
}

#endif //RTYPE_CONNECTSERVERDATAGRAM_HPP
