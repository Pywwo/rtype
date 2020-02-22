/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** StartGameDatagram.hpp
*/

/* Created the 23/11/2019 at 20:06 by jules */

#ifndef RTYPE_STARTGAMEDATAGRAM_HPP
#define RTYPE_STARTGAMEDATAGRAM_HPP

#include <vector>
#include "other/ComponentInfos.hpp"
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
         * @class StartGameDatagram
         * @brief Datagram for start game command
         */
        class StartGameDatagram : public RtypeDatagram {
        public:
            /*!
             * @brief ctor
             */
            StartGameDatagram() = default;
            /*!
             * @brief dtor
             */
             ~StartGameDatagram() = default;

             /*!
              * @brief Create datagram for start game command
              * @param nbComponents The number of components in the array
              * @param components
              */
              void createStartGameDatagram(uint32_t nbComponents, const std::vector<ComponentInfos> &components);
              /*!
               * @brief Extract initial game state from datagram
               */
               void extractStartGameDatagram(uint32_t &nbComponents, std::vector<ComponentInfos> &components);
        };
    }
}

#endif //RTYPE_STARTGAMEDATAGRAM_HPP
