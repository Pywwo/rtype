/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** testCreateLobbyDatagram.cpp
*/

/* Created the 20/11/2019 at 15:37 by jbulteau */

#include <criterion/criterion.h>
#include "CreateLobbyDatagram.hpp"

Test(createLobbyDatagram, create_datagram)
{
    rtype::network::CreateLobbyDatagram datagram;

    datagram.createCreateLobbyDatagram(12345);
    cr_expect_eq(NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode))), 12345);
}

Test(createLobbyDatagram, extract_datagram)
{
    auto opCode = rtype::network::RtypeDatagram::RtypeOpCodeCreateLobby;
    uint64_t userId = HTONLL(12345);
    rtype::network::CreateLobbyDatagram datagram;
    uint32_t size = HTONL(sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint64_t));
    auto *buf = new unsigned char [size];
    std::memcpy(buf, &opCode, sizeof(rtype::network::RtypeDatagram::RtypeOpCode));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode), &userId, sizeof(uint64_t));
    datagram.setData(size, buf);

    uint64_t newUserId;
    datagram.extractCreateLobbyDatagram(newUserId);
    cr_expect_eq(newUserId, 12345);
}