/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** testLeaveGameDatagram.cpp
*/

/* Created the 25/11/2019 at 12:12 by jbulteau */

#include <criterion/criterion.h>
#include "LeaveGameDatagram.hpp"

Test(leaveGameDatagram, create_datagram)
{
    rtype::network::LeaveGameDatagram datagram;

    datagram.createLeaveGameDatagram(12345, 54321);
    cr_expect_eq(NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode))), 12345);
    cr_expect_eq(NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(long))), 54321);
}

Test(leaveGameDatagram, extract_datagram)
{
    auto opCode = rtype::network::RtypeDatagram::RtypeOpCodeLeaveGame;
    uint64_t userId = HTONLL(12345);
    uint64_t lobbyId = HTONLL(54321);
    rtype::network::LeaveGameDatagram datagram;
    size_t size = sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(long) + sizeof(long);
    auto *buf = new unsigned char[size];
    std::memcpy(buf, &opCode, sizeof(rtype::network::RtypeDatagram::RtypeOpCode));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode), &userId, sizeof(long));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(long), &lobbyId, sizeof(long));
    datagram.setData(size, buf);

    uint64_t newUserId;
    uint64_t newLobbyId;
    datagram.extractLeaveGameDatagram(newUserId, newLobbyId);
    cr_expect_eq(newUserId, 12345);
    cr_expect_eq(newLobbyId, 54321);
}