/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** testTriggerBonusDatagram.cpp
*/

/* Created the 24/11/2019 at 15:43 by jbulteau */

#include <criterion/criterion.h>
#include "TriggerBonusDatagram.hpp"

Test(triggerBonusDatagram, create_datagram)
{
    rtype::network::TriggerBonusDatagram datagram;

    datagram.createTriggerBonusDatagram(12345, rtype::BONUS_BASIC);
    cr_expect_eq(NTOHLL(*reinterpret_cast<const long *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode))), 12345);
    cr_expect_eq(*reinterpret_cast<const rtype::RtypeBonusTypes *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint64_t)), rtype::BONUS_BASIC);
}

Test(triggerBonusDatagram, extract_datagram)
{
    auto opCode = rtype::network::RtypeDatagram::RtypeOpCodePlayerDeath;
    uint64_t userId = HTONLL(12345);
    auto bonus = rtype::BONUS_BASIC;
    rtype::network::TriggerBonusDatagram datagram;
    size_t size = sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint64_t) + sizeof(rtype::RtypeBonusTypes);
    auto *buf = new unsigned char[size];
    std::memcpy(buf, &opCode, sizeof(rtype::network::RtypeDatagram::RtypeOpCode));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode), &userId, sizeof(uint64_t));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint64_t), &bonus, sizeof(rtype::RtypeBonusTypes));
    datagram.setData(size, buf);

    uint64_t newUserId;
    rtype::RtypeBonusTypes newBonus;
    datagram.extractTriggerBonusDatagram(newUserId, newBonus);
    cr_expect_eq(newUserId, 12345);
    cr_expect_eq(newBonus, rtype::BONUS_BASIC);
}