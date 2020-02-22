/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** PlayerDeathDatagram.hpp
*/

/* Created the 23/11/2019 at 20:07 by jules */

#ifndef RTYPE_PLAYERDEATHDATAGRAM_HPP
#define RTYPE_PLAYERDEATHDATAGRAM_HPP

#include "RtypeDatagram.hpp"

/*!
 * @namespace rtype
 * @brief Main namespace for all networking
 */
namespace rtype {

    /*!
     * @namespace rtype::network
     * @brief Main namespace for all networking
     */
    namespace network {

        /*!
         * @class PlayerDeathDatagram
         * @brief Datagram for player death command
         */
        class PlayerDeathDatagram : public RtypeDatagram {
        public:
            /*!
             * @brief ctor
             */
             PlayerDeathDatagram() = default;
             /*!
              * @brief dtor
              */
             ~PlayerDeathDatagram() = default;

             /*!
              * @brief Create datagram for player death command
              * @param userId The user id to kill
              */
              void createPlayerDeathDatagram(uint64_t userId);
              /*!
               * @brief Extract user id from datagram
               * @param userId The user id to kill, filled with datagram's content
               */
               void extractPlayerDeathDatagram(uint64_t &userId);
        };
    }
}

#endif //RTYPE_PLAYERDEATHDATAGRAM_HPP
