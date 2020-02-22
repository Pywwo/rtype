/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** Lobby.hpp
*/

/* Created the 20/11/2019 at 16:37 by jbulteau */

#ifndef RTYPE_LOBBY_HPP
#define RTYPE_LOBBY_HPP

#include "Player.hpp"

/*!
 * @namespace rtype
 * @brief Main namespace for all rtype project
 */
namespace rtype {

    /*!
     * @struct Lobby
     * @brief A structure containing lobby's data
     */
    #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
        __pragma(pack(push, 1))
        struct Lobby {
            uint64_t id; /*!< The id of the lobby */
            Player player[4]; /*!< An array containing the players in the lobby */
        } __pragma(pack(pop));
    #else
        struct Lobby {
            uint64_t id; /*!< The id of the lobby */
            Player player[4]; /*!< An array containing the players in the lobby */
        } __attribute__((packed));
    #endif
}

#endif //RTYPE_LOBBY_HPP
