/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** TriggerBonusDatagram.hpp
*/

/* Created the 23/11/2019 at 20:07 by jules */

#ifndef RTYPE_TRIGGERBONUSDATAGRAM_HPP
#define RTYPE_TRIGGERBONUSDATAGRAM_HPP

#include "RtypeDatagram.hpp"
#include "other/BonusType.hpp"

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
         * @class TriggerBonusDatagram
         * @brief Datagram for trigger bonus command
         */
        class TriggerBonusDatagram : public RtypeDatagram {
        public:
            /*!
             * @brief ctor
             */
             TriggerBonusDatagram() = default;
             /*!
              * @brief dtor
              */
              ~TriggerBonusDatagram() = default;

              /*!
               * @brief Create datagram for leave lobby command
               * @param userId The user id affected by the bonus
               */
               void createTriggerBonusDatagram(uint64_t userId, RtypeBonusTypes bonus);
               /*!
                * @brief Extract user id from datagram
                * @param userId The user id affected by the bonus, filled with datagram's content
                */
                void extractTriggerBonusDatagram(uint64_t &userId, RtypeBonusTypes &bonus);
        };
    }
}

#endif //RTYPE_TRIGGERBONUSDATAGRAM_HPP
