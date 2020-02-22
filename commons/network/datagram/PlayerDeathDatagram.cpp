/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** PlayerDeathDatagram.cpp
*/

/* Created the 23/11/2019 at 20:07 by jules */

#include "PlayerDeathDatagram.hpp"
#include <cstring>

void rtype::network::PlayerDeathDatagram::createPlayerDeathDatagram(uint64_t userId)
{
    size_t size = sizeof(RtypeOpCode) + sizeof(userId);
    auto *buf = new unsigned char[size];
    RtypeOpCode opCode = RtypeOpCodePlayerDeath;

    userId = HTONLL(userId);
    std::memcpy(buf, &opCode, sizeof(RtypeOpCode));
    std::memcpy(buf + sizeof(RtypeOpCode), &userId, sizeof(userId));
    setData(size, buf);
    delete [] buf;
}

void rtype::network::PlayerDeathDatagram::extractPlayerDeathDatagram(uint64_t &userId)
{
    if (sizeof(RtypeOpCode) + sizeof(userId) > getSize()) {
        return;
    }
    userId = NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode)));
}
