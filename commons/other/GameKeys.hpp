/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** GameKeys.hpp
*/

/* Created the 20/11/2019 at 18:37 by jbulteau */

#ifndef RTYPE_GAMEKEYS_HPP
#define RTYPE_GAMEKEYS_HPP

/*!
 * @namespace rtype
 * @brief Main namespace for all rtype project
 */
namespace rtype {

    /*!
     * @enum RtypeGameKeys
     * @brief An enum binding in-game key related events
     */
    enum RtypeGameKeys {
        KEY_UP = 1,
        KEY_LEFT = 2,
        KEY_RIGHT = 3,
        KEY_DOWN = 4,
        KEY_SHOOT = 5
    };

    /*!
     * @enum RtypeKeyState
     * @brief An enum binding in-game key state related events
     */
    enum RtypeKeyState {
        KEY_PRESSED = 1,
        KEY_RELEASED = 2
    };
}

#endif //RTYPE_GAMEKEYS_HPP
