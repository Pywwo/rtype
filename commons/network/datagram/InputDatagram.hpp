/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** InputDatagram.hpp
*/

/* Created the 20/11/2019 at 15:09 by jbulteau */

#ifndef RTYPE_INPUTDATAGRAM_HPP
#define RTYPE_INPUTDATAGRAM_HPP

#include "other/GameKeys.hpp"
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
         * @class InputDatagram
         * @brief Datagram for input command
         */
        class InputDatagram : public RtypeDatagram {
        public:
            /*!
             * @brief ctor
             */
            InputDatagram() = default;
            /*!
             * @brief dtor
             */
            ~InputDatagram() = default;

            /*!
             * @brief Create datagram for input command
             * @param userId The user id
             * @param lobbyId The lobby id
             * @param key The key pressed/released
             * @param state The state of the key
             */
            void createInputDatagram(uint64_t userId, uint64_t lobbyId, RtypeGameKeys key, RtypeKeyState state);
            /*!
             * @brief Extract input from datagram
             * @param userId The user id filled with datagram's content
             * @param lobbyId The lobby id filled with datagram's content
             * @param key The key pressed/released filled with datagram's content
             * @param state The state of the key filled with datagram's content
             */
            void extractInputDatagram(uint64_t &userId, uint64_t &lobbyId, RtypeGameKeys &key, RtypeKeyState &state);
        };
    }
}

#endif //RTYPE_INPUTDATAGRAM_HPP
