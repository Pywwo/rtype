/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** ConnectLobbyDatagram.hpp
*/

/* Created the 23/11/2019 at 19:38 by jules */

#ifndef RTYPE_CONNECTLOBBYDATAGRAM_HPP
#define RTYPE_CONNECTLOBBYDATAGRAM_HPP

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
         * @class ConnectLobbyDatagram
         * @brief Datagram for connect to lobby command
         */
        class ConnectLobbyDatagram : public RtypeDatagram {
        public:
            /*!
             * @brief ctor
             */
            ConnectLobbyDatagram() = default;
            /*!
             * @brief dtor
             */
            ~ConnectLobbyDatagram() = default;

            /*!
             * @brief Create datagram for connect to lobby command
             * @param userId The user id
             * @param lobbyId The lobby id to connect
             */
            void createConnectLobbyDatagram(uint64_t userId, uint64_t lobbyId);
            /*!
             * @brief Extract user and lobby ids from datagram
             * @param userId The user id filled with datagram's content
             * @param lobbyId The lobby id filled with datagram's content
             */
            void extractConnectLobbyDatagram(uint64_t &userId, uint64_t &lobbyId);
        };
    }
}

#endif //RTYPE_CONNECTLOBBYDATAGRAM_HPP
