/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** AvailableLobbiesDatagram.hpp
*/

/* Created the 20/11/2019 at 15:08 by jbulteau */

#ifndef RTYPE_AVAILABLELOBBIESDATAGRAM_HPP
#define RTYPE_AVAILABLELOBBIESDATAGRAM_HPP

#include <vector>
#include "other/Lobby.hpp"
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
         * @class AvailableLobbiesDatagram
         * @brief Datagram for available lobbies command
         */
        class AvailableLobbiesDatagram : public RtypeDatagram {
        public:
            /*!
             * @brief ctor
             */
            AvailableLobbiesDatagram() = default;
            /*!
             * @brief dtor
             */
            ~AvailableLobbiesDatagram() = default;

            /*!
             * @brief Create datagram for available lobbies command
             * @param lobbies An array of available lobbies
             */
            void createAvailableLobbiesDatagram(uint32_t nbLobby, const std::vector<Lobby> &lobbies);
            /*!
             * @brief Extract available lobbies from datagram
             * @param lobbies An array of lobbies filled with datagram's content
             */
            void extractAvailableLobbiesDatagram(uint32_t &nbLobby, std::vector<Lobby> &lobbies);
        };
    }
}

#endif //RTYPE_AVAILABLELOBBIESDATAGRAM_HPP
