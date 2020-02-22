/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** SpawnEnemyDatagram.hpp
*/

/* Created the 24/11/2019 at 17:40 by jbulteau */

#ifndef RTYPE_SPAWNENEMYDATAGRAM_HPP
#define RTYPE_SPAWNENEMYDATAGRAM_HPP

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
         * @class SpawnEnemyDatagram
         * @brief Datagram for spawn enemy command
         */
        class SpawnEnemyDatagram : public RtypeDatagram {
        public:
            /*!
             * @brief ctor
             */
             SpawnEnemyDatagram() = default;
             /*!
              * @brief dtor
              */
              ~SpawnEnemyDatagram() = default;

              /*!
               * @brief Create datagram for spawn enemy command
               * @param enemyId The id of the enemy to create
               * @param position The position where the enemy must spawn
               * @param name The name of the enemy
               */
               void createSpawnEnemyDatagram(uint64_t enemyId, const std::pair<float, float> &position, const std::string &name);
               /*!
                * @brief Extract new enemy from datagram
                * @param enemyId The id of the enemy to create filled with datagram's content
                * @param position The position where the enemy must spawn filled with datagram's content
                * @param name The name of the enemy filled with datagram's content
                */
                void extractSpawnEnemyDatagram(uint64_t &enemyId, std::pair<float, float> &position, std::string &name);
        };
    }
}

#endif //RTYPE_SPAWNENEMYDATAGRAM_HPP
