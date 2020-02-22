/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** testPlayerDeathDatagram.cpp
*/

/* Created the 24/11/2019 at 15:42 by jbulteau */

#include <criterion/criterion.h>
#include "PlayerDeathDatagram.hpp"

Test(playerDeathDatagram, create_datagram)
{
    rtype::network::PlayerDeathDatagram datagram;

    datagram.createPlayerDeathDatagram(12345);
    cr_expect_eq(NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode))), 12345);
}

Test(playerDeathDatagram, extract_datagram)
{
    auto opCode = rtype::network::RtypeDatagram::RtypeOpCodePlayerDeath;
    uint64_t userId = HTONLL(12345);
    rtype::network::PlayerDeathDatagram datagram;
    size_t size = sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint64_t);
    auto *buf = new unsigned char[size];
    std::memcpy(buf, &opCode, sizeof(rtype::network::RtypeDatagram::RtypeOpCode));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode), &userId, sizeof(uint64_t));
    datagram.setData(size, buf);

    uint64_t newUserId;
    datagram.extractPlayerDeathDatagram(newUserId);
    cr_expect_eq(newUserId, 12345);
}