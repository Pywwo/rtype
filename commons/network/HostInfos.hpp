/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** HostInfos
*/

#ifndef RTYPE_HOSTINFOS_HPP
#define RTYPE_HOSTINFOS_HPP

#include <string>

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
         * @struct HostInfos
         * @brief A structure holding host information
         */
        struct HostInfos {
            std::string host; /*!< The host as an address or a domain */
            int port; /*!< The port for this host */
        };
    }
}

#endif //RTYPE_HOSTINFOS_HPP