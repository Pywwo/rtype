/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** CreateLobbyDatagram.cpp
*/

/* Created the 20/11/2019 at 15:04 by jbulteau */

#include "CreateLobbyDatagram.hpp"
#include <cstring>

void rtype::network::CreateLobbyDatagram::createCreateLobbyDatagram(uint64_t userId)
{
    size_t size = sizeof(RtypeOpCode) + sizeof(userId);
    auto *buf = new unsigned char[size];
    RtypeOpCode opCode = RtypeOpCodeCreateLobby;

    userId = HTONLL(userId);
    std::memcpy(buf, &opCode, sizeof(RtypeOpCode));
    std::memcpy(buf + sizeof(RtypeOpCode), &userId, sizeof(userId));
    setData(size, buf);
    delete [] buf;
}

void rtype::network::CreateLobbyDatagram::extractCreateLobbyDatagram(uint64_t &userId)
{
    if (sizeof(RtypeOpCode) + sizeof(userId) > getSize()) {
        return;
    }
    userId = NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode)));
}
