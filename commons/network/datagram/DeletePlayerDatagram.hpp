/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** DeletePlayerDatagram.hpp
*/

/* Created the 29/11/2019 at 18:48 by acarlier */

#ifndef RTYPE_DELETEPLAYERDATAGRAM_HPP
#define RTYPE_DELETEPLAYERDATAGRAM_HPP

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
         * @class DeletePlayerDatagram
         * @brief Datagram for delete player command
         */
        class DeletePlayerDatagram : public RtypeDatagram {
        public:
            /*!
             * @brief ctor
             */
            DeletePlayerDatagram() = default;
            /*!
             * @brief dtor
             */
            ~DeletePlayerDatagram() = default;

            /*!
             * @brief Create a datagram for delete player command
             * @param playerName The player who left the game
             */
            void createDeletePlayerDatagram(const std::string &playerName);
            /*!
             * @brief Extract infos from datagram
             * @param playerName The player who left the game filled with datagram's content
             */
            void extractDeletePlayerDatagram(std::string &playerName);
        };
    }
}
#endif