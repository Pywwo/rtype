/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** testFetchLobbiesDatagram.cpp
*/

/* Created the 20/11/2019 at 18:05 by jbulteau */

#include <criterion/criterion.h>
#include "FetchLobbiesDatagram.hpp"

Test(fetchLobbiesDatagram, create_datagram)
{
    rtype::network::FetchLobbiesDatagram datagram;

    datagram.createFetchLobbiesDatagram(12345);
    cr_expect_eq(NTOHLL(*reinterpret_cast<const long *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode))), 12345);
}

Test(fetchLobbiesDatagram, extract_datagram)
{
    auto opCode = rtype::network::RtypeDatagram::RtypeOpCodeCreateLobby;
    uint64_t userId = HTONLL(12345);
    rtype::network::FetchLobbiesDatagram datagram;
    size_t size = sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(long);
    auto *buf = new unsigned char [size];
    std::memcpy(buf, &opCode, sizeof(rtype::network::RtypeDatagram::RtypeOpCode));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode), &userId, sizeof(long));
    datagram.setData(size, buf);

    uint64_t newUserId;
    datagram.extractFetchLobbiesDatagram(newUserId);
    cr_expect_eq(newUserId, 12345);
}