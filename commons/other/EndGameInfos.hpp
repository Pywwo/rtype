/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** EndGameInfos.hpp
*/

/* Created the 20/11/2019 at 18:12 by jbulteau */

#ifndef RTYPE_ENDGAMEINFOS_HPP
#define RTYPE_ENDGAMEINFOS_HPP

/*!
 * @namespace rtype
 * @brief Main namespace for all rtype project
 */
namespace rtype {

    /*!
     * @struct EndGameInfos
     * @brief A structure containing game's data
     */
    #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
        __pragma(pack(push, 1))
        struct EndGameInfos {
            unsigned int score; /*!< The final score of the game */
        } __pragma(pack(pop));
    #else
        struct EndGameInfos {
            unsigned int score; /*!< The final score of the game */
        } __attribute__((packed));
    #endif
}

#endif //RTYPE_ENDGAMEINFOS_HPP
