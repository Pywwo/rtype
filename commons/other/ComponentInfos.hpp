/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** ComponentInfos.hpp
*/

/* Created the 24/11/2019 at 17:43 by jbulteau */

#ifndef RTYPE_COMPONENTINFOS_HPP
#define RTYPE_COMPONENTINFOS_HPP

#include <string>

/*!
 * @namespace rtype
 * @brief Main namespace for all rtype project
 */
namespace rtype {

    /*!
     * @struct Component infos
     * @brief A structure containing component's data for updates
     */
    #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
        __pragma(pack(push, 1))
        struct ComponentInfos {
            char entityName[20]; /*!< The entity to update */
            std::pair<float, float> position; /*!< The new position of the entity (not taken in consideration if velocity is not null) */
            std::pair<float, float> velocity; /*!< The new velocity of the entity (if null, position is used instead) */
            int isAlive;
        } __pragma(pack(pop));
    #else
        struct ComponentInfos {
            char entityName[20]; /*!< The entity to update */
            std::pair<float, float> position; /*!< The new position of the entity (not taken in consideration if velocity is not null) */
            std::pair<float, float> velocity; /*!< The new velocity of the entity (if null, position is used instead) */
            int isAlive;
        } __attribute__((packed));
    #endif
}

#endif //RTYPE_COMPONENTINFOS_HPP
