/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** TriggerBonusDatagram.cpp
*/

/* Created the 23/11/2019 at 20:07 by jules */

#include "TriggerBonusDatagram.hpp"
#include <cstring>

void rtype::network::TriggerBonusDatagram::createTriggerBonusDatagram(uint64_t userId, RtypeBonusTypes bonus)
{
    size_t size = sizeof(RtypeOpCode) + sizeof(userId) + sizeof(bonus);
    auto *buf = new unsigned char[size];
    RtypeOpCode opCode = RtypeOpCodeTriggerBonus;

    userId = HTONLL(userId);
    std::memcpy(buf, &opCode, sizeof(RtypeOpCode));
    std::memcpy(buf + sizeof(RtypeOpCode), &userId, sizeof(userId));
    std::memcpy(buf + sizeof(RtypeOpCode) + sizeof(userId), &bonus, sizeof(bonus));
    setData(size, buf);
    delete [] buf;
}

void rtype::network::TriggerBonusDatagram::extractTriggerBonusDatagram(uint64_t &userId, RtypeBonusTypes &bonus)
{
    if (sizeof(RtypeOpCode) + sizeof(userId) + sizeof(bonus) > getSize()) {
        return;
    }
    userId = NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode)));
    bonus = *reinterpret_cast<const RtypeBonusTypes *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode) + sizeof(userId));
}
