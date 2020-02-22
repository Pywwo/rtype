/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** EndGameDatagram.hpp
*/

/* Created the 20/11/2019 at 15:10 by jbulteau */

#ifndef RTYPE_ENDGAMEDATAGRAM_HPP
#define RTYPE_ENDGAMEDATAGRAM_HPP

#include "other/EndGameInfos.hpp"
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
         * @class EndGameDatagram
         * @brief Datagram for end game command
         */
        class EndGameDatagram : public RtypeDatagram {
        public:
            /*!
             * @brief ctor
             */
            EndGameDatagram() = default;
            /*!
             * @brief dtor
             */
            ~EndGameDatagram() = default;

            /*!
             * @brief Create datagram for end game command
             * @param infos The game's data
             */
            void createEndGameDatagram(const EndGameInfos &infos);
            /*!
             * @brief Extract infos from datagram
             * @param infos The game's data filled with datagram's content
             */
            void extractEndGameDatagram(EndGameInfos &infos);
        };
    }
}

#endif //RTYPE_ENDGAMEDATAGRAM_HPP
