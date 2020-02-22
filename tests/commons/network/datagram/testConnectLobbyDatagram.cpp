/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** testConnectLobbyDatagram.cpp
*/

/* Created the 24/11/2019 at 15:40 by jbulteau */

#include <criterion/criterion.h>
#include "ConnectLobbyDatagram.hpp"
#include "AvailableLobbiesDatagram.hpp"

Test(connectLobbyDatagram, create_datagram)
{
    rtype::network::ConnectLobbyDatagram datagram;

    datagram.createConnectLobbyDatagram(12345, 54321);
    cr_expect_eq(NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode))), 12345);
    cr_expect_eq(NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint64_t))), 54321);
}

Test(connectLobbyDatagra, extract_datagram)
{
    auto opCode = rtype::network::RtypeDatagram::RtypeOpCodeConnectLobby;
    uint64_t userId = HTONLL(12345);
    uint64_t lobbyId = HTONLL(54321);
    rtype::network::ConnectLobbyDatagram datagram;
    uint32_t size = NTOHL(sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint64_t) + sizeof(uint64_t));
    auto *buf = new unsigned char[size];
    std::memcpy(buf, &opCode, sizeof(rtype::network::RtypeDatagram::RtypeOpCode));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode), &userId, sizeof(uint64_t));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint64_t), &lobbyId, sizeof(uint64_t));
    datagram.setData(size, buf);

    uint64_t newUserId;
    uint64_t newLobbyId;
    datagram.extractConnectLobbyDatagram(newUserId, newLobbyId);
    cr_expect_eq(newUserId, 12345);
    cr_expect_eq(newLobbyId, 54321);
}