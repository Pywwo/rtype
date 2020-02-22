/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** EnemyDeathDatagram.hpp
*/

/* Created the 24/11/2019 at 17:41 by jbulteau */

#ifndef RTYPE_ENEMYDEATHDATAGRAM_HPP
#define RTYPE_ENEMYDEATHDATAGRAM_HPP

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
         * @class EnemyDeathDatagram
         * @brief Datagram for enemy death command
         */
        class EnemyDeathDatagram : public RtypeDatagram {
        public:
            /*!
             * @brief ctor
             */
            EnemyDeathDatagram() = default;
            /*!
             * @brief dtor
             */
            ~EnemyDeathDatagram() = default;

            /*!
             * @brief Create datagram for enemy death command
             * @param enemyId The id of the dead enemy
             */
            void createEnemyDeathDatagram(uint64_t enemyId);
            /*!
             * @brief Extract enemy id from datagram
             * @param enemyId The id of the dead enemy filled with datagram's content
             */
            void extractEnemyDeathDatagram(uint64_t &enemyId);
        };
    }
}

#endif //RTYPE_ENEMYDEATHDATAGRAM_HPP
