/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** datagram.hpp
*/

/* Created the 18/11/2019 at 16:38 by jbulteau */

#ifndef RTYPE_DATAGRAM_HPP
#define RTYPE_DATAGRAM_HPP

#include <cstddef>
#include "HostInfos.hpp"

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
         * @class Datagram
         * @brief A class for basic UDP datagrams
         */
        class Datagram {
        public:
            /*!
             * @brief ctor
             */
            Datagram();
            /*!
             * @brief ctor
             * @param hostInfos A structure containing host's data (ip address and port)
             */
            explicit Datagram(const HostInfos &hostInfos);
            /*!
             * @brief ctor
             * @param size The data size
             * @param data The data to send through the datagram
             */
            Datagram(size_t size, void *data);
            /*!
             * @brief ctor
             * @param hostInfos A structure containing host's data (ip address and port)
             * @param size The data size
             * @param data The data to send through the datagram
             */
            Datagram(const HostInfos &hostInfos, size_t size, void *data);
            /*!
             * @brief copy ctor
             * @param datagram The datagram to copy
             */
            Datagram(const Datagram &datagram);
            /*!
             * @brief dtor
             */
            ~Datagram();

            /*!
             * @brief HostInfos setter
             * @param hostInfos A structure containing host's data (ip address and port)
             */
            void setHostInfos(const HostInfos &hostInfos);
            /*!
             * @brief HostInfos getter
             * @return A structure containing host's data (ip address and port)
             */
            [[nodiscard]] const HostInfos &getHostInfos() const;
            /*!
             * @brief Data setter
             * @param size The data size
             * @param data The data to send through the datagram
             */
            void setData(size_t size, void *data);
            /*!
             * @brief Size getter
             * @return The size of the data contained in the datagram
             */
            [[nodiscard]] size_t getSize() const;
            /*!
             * @brief Data getter
             * @return The data contained in the datagram
             */
            [[nodiscard]] const void *getData() const;
            /*!
             * @brief Clear datagram's content
             */
            void clear();

        private:
            HostInfos _hostInfos; /*!< A structure containing host's data (ip address and port) */
            size_t _size; /*!< The datagram's data size */
            void *_data; /*!< The datagram's data */

        };
    }
}

#endif //RTYPE_DATAGRAM_HPP