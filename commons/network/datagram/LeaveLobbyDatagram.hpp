/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** LeaveLobbyDatagram.hpp
*/

/* Created the 23/11/2019 at 19:37 by jules */

#ifndef RTYPE_LEAVELOBBYDATAGRAM_HPP
#define RTYPE_LEAVELOBBYDATAGRAM_HPP

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
         * @class LeaveLobbyDatagram
         * @brief Datagram for leave lobby command
         */
        class LeaveLobbyDatagram : public RtypeDatagram {
        public:
            /*!
             * @brief ctor
             */
             LeaveLobbyDatagram() = default;
             /*!
              * @brief dtor
              */
              ~LeaveLobbyDatagram() = default;

              /*!
               * @brief Create datagram for leave lobby command
               * @param userId The user id
               * @param lobbyId The lobby id to leave
               */
               void createLeaveLobbyDatagram(uint64_t userId, uint64_t lobbyId);
               /*!
                * @brief Extract user and lobby ids from datagram
                * @param userId The user id filled with datagram's content
                * @param lobbyId The lobby id filled with datagram's content
                */
                void extractLeaveLobbyDatagram(uint64_t &userId, uint64_t &lobbyId);
        };
    }
}

#endif //RTYPE_LEAVELOBBYDATAGRAM_HPP
