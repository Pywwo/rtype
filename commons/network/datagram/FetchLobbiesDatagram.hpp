/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** FetchLobbiesDatagram.hpp
*/

/* Created the 20/11/2019 at 15:05 by jbulteau */

#ifndef RTYPE_FETCHLOBBIESDATAGRAM_HPP
#define RTYPE_FETCHLOBBIESDATAGRAM_HPP

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
         * @class FetchLobbiesDatagram
         * @brief Datagram for fetch lobbies command
         */
        class FetchLobbiesDatagram : public RtypeDatagram {
        public:
            /*!
             * @brief ctor
             */
            FetchLobbiesDatagram() = default;
            /*!
             * @brief dtor
             */
            ~FetchLobbiesDatagram() = default;

            /*!
             * @brief Create datagram for fetch lobbies command
             * @param userId The user id
             */
            void createFetchLobbiesDatagram(uint64_t userId);
            /*!
             * @brief Extract infos from datagram
             * @param userId The user id filled with datagram's content
             */
            void extractFetchLobbiesDatagram(uint64_t &userId);
        };
    }
}

#endif //RTYPE_FETCHLOBBIESDATAGRAM_HPP
