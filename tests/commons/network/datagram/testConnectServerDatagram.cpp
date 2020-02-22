/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** testConnectServerDatagram.cpp
*/

/* Created the 27/11/2019 at 16:01 by jbulteau */

#include <criterion/criterion.h>
#include "ConnectServerDatagram.hpp"

Test(connectServerDatagram, create_datagram)
{
    rtype::network::ConnectServerDatagram datagram;
    datagram.createConnectServerDatagram(12345, 8080);

    uint64_t userId = NTOHLL(*reinterpret_cast<const long *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode)));
    int port;
    port = NTOHLL(*reinterpret_cast<const int *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(long)));
    cr_expect_eq(userId, 12345);
    cr_expect_eq(port, 8080);
}

Test(connectServerDatagram, extract_datagram)
{
    auto opCode = rtype::network::RtypeDatagram::RtypeOpCodeConnectServer;
    uint64_t userId = HTONLL(12345);
    int port = HTONL(8080);
    rtype::network::ConnectServerDatagram datagram;
    size_t size = sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint64_t) + sizeof(int);
    auto *buf = new unsigned char[size];
    std::memcpy(buf, &opCode, sizeof(rtype::network::RtypeDatagram::RtypeOpCode));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode), &userId, sizeof(uint64_t));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint64_t), &port, sizeof(int));
    datagram.setData(size, buf);

    uint64_t newUserId;
    int newPort;
    datagram.extractConnectServerDatagram(newUserId, newPort);
    cr_expect_eq(newUserId, 12345);
    cr_expect_eq(newPort, 8080);
}