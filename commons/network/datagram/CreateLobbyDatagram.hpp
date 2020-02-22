/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** CreateLobbyDatagram.hpp
*/

/* Created the 20/11/2019 at 15:04 by jbulteau */

#ifndef RTYPE_CREATELOBBYDATAGRAM_HPP
#define RTYPE_CREATELOBBYDATAGRAM_HPP

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
         * @class CreateLobbyDatagram
         * @brief Datagram for create lobby command
         */
        class CreateLobbyDatagram : public RtypeDatagram {
        public:
            /*!
             * @brief ctor
             */
            CreateLobbyDatagram() = default;
            /*!
             * @brief dtor
             */
            ~CreateLobbyDatagram() = default;

            /*!
             * @brief Create datagram for create lobby command
             * @param userId The user id
             */
            void createCreateLobbyDatagram(uint64_t userId);
            /*!
             * @brief Extract user id from datagram
             * @param userId The user id filled with datagram's content
             */
            void extractCreateLobbyDatagram(uint64_t &userId);
        };
    }
}

#endif //RTYPE_CREATELOBBYDATAGRAM_HPP
