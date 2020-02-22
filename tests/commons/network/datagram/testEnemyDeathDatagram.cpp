/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** testEnemyDeathDatagram.cpp
*/

/* Created the 24/11/2019 at 18:46 by jbulteau */

#include <criterion/criterion.h>
#include "EnemyDeathDatagram.hpp"

Test(enemyDeathDatagram, create_datagram)
{
    rtype::network::EnemyDeathDatagram datagram;

    datagram.createEnemyDeathDatagram(12345);
    cr_expect_eq(NTOHLL(*reinterpret_cast<const long *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode))), 12345);
}

Test(enemyDeathDatagram, extract_datagram)
{
    auto opCode = rtype::network::RtypeDatagram::RtypeOpCodeEnemyDeath;
    uint64_t userId = HTONLL(12345);
    rtype::network::EnemyDeathDatagram datagram;
    size_t size = sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(long);
    auto *buf = new unsigned char[size];
    std::memcpy(buf, &opCode, sizeof(rtype::network::RtypeDatagram::RtypeOpCode));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode), &userId, sizeof(long));
    datagram.setData(size, buf);

    uint64_t newUserId;
    datagram.extractEnemyDeathDatagram(newUserId);
    cr_expect_eq(newUserId, 12345);
}