/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** BinaryDatagram.hpp
*/

/* Created the 20/11/2019 at 15:10 by jbulteau */

#ifndef RTYPE_BINARYDATAGRAM_HPP
#define RTYPE_BINARYDATAGRAM_HPP

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
         * @class BinaryDatagram
         * @brief Datagram for binary command, mostly used to answer a previous command
         */
        class BinaryDatagram : public RtypeDatagram {
        public:
            /*!
             * @brief ctor
             */
            BinaryDatagram() = default;
            /*!
             * @brief dtor
             */
            ~BinaryDatagram() = default;

            /*!
             * @brief Create datagram for binary command
             * @param value The value to send : OK/KO (true/false)
             * @param description The description of the response if needed
             */
            void createBinaryDatagram(bool value, const std::string &description);
            /*!
             * @brief Extract value from datagram
             * @param value The value filled with datagram's content
             * @param description The description of the response filled with datagram's content
             */
            void extractBinaryDatagram(bool &value, std::string &description);
        };
    }
}

#endif //RTYPE_BINARYDATAGRAM_HPP
