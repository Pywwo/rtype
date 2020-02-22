/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** LeaveGameDatagram.hpp
*/

/* Created the 25/11/2019 at 11:48 by jbulteau */

#ifndef RTYPE_LEAVEGAMEDATAGRAM_HPP
#define RTYPE_LEAVEGAMEDATAGRAM_HPP

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
         * @class LeaveGameDatagram
         * @brief Datagram for leave game command
         */
        class LeaveGameDatagram: public RtypeDatagram {
        public:
            /*!
             * @brief ctor
             */
             LeaveGameDatagram() = default;
             /*!
              * @brief dtor
              */
              ~LeaveGameDatagram() = default;

              /*!
               * @brief Create datagram for leave game command
               * @param userId The user id
               * @param lobbyId The lobby id to leave
               */
              void createLeaveGameDatagram(uint64_t userId, uint64_t lobbyId);
              /*!
               * @brief Extract user and lobby ids from datagram
               * @param userId The user id filled with datagram's content
               * @param lobbyId The lobby id filled with datagram's content
               */
              void extractLeaveGameDatagram(uint64_t &userId, uint64_t &lobbyId);
        };
    }
}

#endif //RTYPE_LEAVEGAMEDATAGRAM_HPP
