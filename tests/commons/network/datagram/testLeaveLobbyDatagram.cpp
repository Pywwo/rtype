/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** testLeaveLobbyDatagram.cpp
*/

/* Created the 24/11/2019 at 15:41 by jbulteau */

#include <criterion/criterion.h>
#include "LeaveLobbyDatagram.hpp"

Test(leaveLobbyDatagram, create_datagram)
{
    rtype::network::LeaveLobbyDatagram datagram;

    datagram.createLeaveLobbyDatagram(12345, 54321);
    cr_expect_eq(NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode))), 12345);
    cr_expect_eq(NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(long))), 54321);
}

Test(leaveLobbyDatagra, extract_datagram)
{
    auto opCode = rtype::network::RtypeDatagram::RtypeOpCodeLeaveLobby;
    uint64_t userId = HTONLL(12345);
    uint64_t lobbyId = HTONLL(54321);
    rtype::network::LeaveLobbyDatagram datagram;
    size_t size = sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint64_t) + sizeof(uint64_t);
    auto *buf = new unsigned char[size];
    std::memcpy(buf, &opCode, sizeof(rtype::network::RtypeDatagram::RtypeOpCode));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode), &userId, sizeof(uint64_t));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint64_t), &lobbyId, sizeof(uint64_t));
    datagram.setData(size, buf);

    uint64_t newUserId;
    uint64_t newLobbyId;
    datagram.extractLeaveLobbyDatagram(newUserId, newLobbyId);
    cr_expect_eq(newUserId, 12345);
    cr_expect_eq(newLobbyId, 54321);
}