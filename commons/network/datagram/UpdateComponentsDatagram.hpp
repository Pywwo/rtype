/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** UpdateComponentsDatagram.hpp
*/

/* Created the 24/11/2019 at 17:41 by jbulteau */

#ifndef RTYPE_UPDATECOMPONENTSDATAGRAM_HPP
#define RTYPE_UPDATECOMPONENTSDATAGRAM_HPP

#include <vector>
#include "RtypeDatagram.hpp"
#include "other/ComponentInfos.hpp"

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
         * @class UpdateComponentsDatagram
         * @brief Datagram for update component command
         */
        class UpdateComponentsDatagram : public RtypeDatagram {
        public:
            /*!
             * @brief ctor
             */
            UpdateComponentsDatagram() = default;
            /*!
             * @brief dtor
             */
            ~UpdateComponentsDatagram() = default;

            /*!
             * @brief Create datagram for update components command
             * @param componentInfos The updated component's data
             */
            void createUpdateComponentDatagram(uint32_t nbComponents, const std::vector<ComponentInfos> &components);
            /*!
             * @brief Extract updated component from datagram
             * @param componentInfos The updated component's data filled with datagram's content
             */
            void extractUpdateComponentDatagram(uint32_t &nbComponents, std::vector<ComponentInfos> &components);
        };
    }
}

#endif //RTYPE_UPDATECOMPONENTSDATAGRAM_HPP
