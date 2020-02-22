/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** RequestStartGameDatagram.hpp
*/

/* Created the 23/11/2019 at 20:09 by jules */

#ifndef RTYPE_REQUESTSTARTGAMEDATAGRAM_HPP
#define RTYPE_REQUESTSTARTGAMEDATAGRAM_HPP

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
         * @class RequestStartGameDatagram
         * @brief Datagram for request start game command
         */
        class RequestStartGameDatagram : public RtypeDatagram {
        public:
            /*!
             * @brief ctor
             */
             RequestStartGameDatagram() = default;
             /*!
              * @brief dtor
              */
              ~RequestStartGameDatagram() = default;

              /*!
               * @brief Create datagram for request start game command
               * @param userId The user id
               * @param lobbyId The lobby id
               */
               void createRequestStartGameDatagram(uint64_t userId, uint64_t lobbyId);
               /*!
                * @brief Extract user and lobby ids from datagram
                * @param userId The user id filled with datagram's content
                * @param lobbyId The lobby id filled with datagram's content
                */
                void extractRequestStartGameDatagram(uint64_t &userId, uint64_t &lobbyId);
        };
    }
}

#endif //RTYPE_REQUESTSTARTGAMEDATAGRAM_HPP
