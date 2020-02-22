/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** ConnectServerDatagram.cpp
*/

/* Created the 27/11/2019 at 15:43 by jbulteau */

#include <cstring>
#include "ConnectServerDatagram.hpp"

void rtype::network::ConnectServerDatagram::createConnectServerDatagram(uint64_t userId, int port)
{
    size_t size = sizeof(RtypeOpCode) + sizeof(userId) + sizeof(port);
    auto *buf = new unsigned char[size];
    RtypeOpCode opCode = RtypeOpCodeConnectServer;

    userId = HTONLL(userId);
    port = HTONL(port);
    std::memcpy(buf, &opCode, sizeof(RtypeOpCode));
    std::memcpy(buf + sizeof(RtypeOpCode), &userId, sizeof(userId));
    std::memcpy(buf + sizeof(RtypeOpCode) + sizeof(userId), &port, sizeof(port));
    setData(size, buf);
    delete [] buf;
}

void rtype::network::ConnectServerDatagram::extractConnectServerDatagram(uint64_t &userId, int &port)
{
    if (sizeof(RtypeOpCode) + sizeof(uint64_t) + sizeof(port) > getSize()) {
        return;
    }
    userId = NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode)));
    port = NTOHL(*reinterpret_cast<const int *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode) + sizeof(uint64_t)));
}
