/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** Player.hpp
*/

/* Created the 20/11/2019 at 16:38 by jbulteau */

#ifndef RTYPE_PLAYER_HPP
#define RTYPE_PLAYER_HPP

#include <string>

/*!
 * @namespace rtype
 * @brief Main namespace for all rtype project
 */
namespace rtype {

    /*!
     * @struct Player
     * @brief A structure containing player's data
     */
    #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
        __pragma(pack(push, 1))
        struct Player {
            uint64_t id; /*!< The id of the player */
            char name[10]; /*!< The name of the player */
        } __pragma(pack(pop));
    #else
        struct Player {
            uint64_t id; /*!< The id of the player */
            char name[10]; /*!< The name of the player */
        } __attribute__((packed));
    #endif
}

#endif //RTYPE_PLAYER_HPP
