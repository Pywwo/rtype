/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** LobbyInfosDatagram.hpp
*/

/* Created the 23/11/2019 at 19:38 by jules */

#ifndef RTYPE_LOBBYINFOSDATAGRAM_HPP
#define RTYPE_LOBBYINFOSDATAGRAM_HPP

#include "RtypeDatagram.hpp"
#include "other/Lobby.hpp"

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
         * @class LobbyInfosDatagram
         * @brief Datagram for lobby infos command
         */
        class LobbyInfosDatagram : public RtypeDatagram {
        public:
            /*!
             * @brief ctor
             */
             LobbyInfosDatagram() = default;
             /*!
              * @brief dtor
              */
              ~LobbyInfosDatagram() = default;

              /*!
               * @brief Create datagram for lobby infos command
               * @param lobby The requested lobby
               */
               void createLobbyInfosDatagram(const Lobby &lobby);
               /*!
                * @brief Extract lobby infos from datagram
                * @param lobby The requested lobby filled with datagram's content
                */
                void extractLobbyInfosDatagram(Lobby &lobby);
        };
    }
}

#endif //RTYPE_LOBBYINFOSDATAGRAM_HPP
