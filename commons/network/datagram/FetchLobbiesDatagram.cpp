/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** FetchLobbiesDatagram.cpp
*/

/* Created the 20/11/2019 at 15:05 by jbulteau */

#include <cstring>
#include "FetchLobbiesDatagram.hpp"

void rtype::network::FetchLobbiesDatagram::createFetchLobbiesDatagram(uint64_t userId)
{
    size_t size = sizeof(RtypeOpCode) + sizeof(userId);
    auto *buf = new unsigned char[size];
    RtypeOpCode opCode = RtypeOpCodeFetchLobbies;

    userId = HTONLL(userId);
    std::memcpy(buf, &opCode, sizeof(RtypeOpCode));
    std::memcpy(buf + sizeof(RtypeOpCode), &userId, sizeof(userId));
    setData(size, buf);
    delete [] buf;
}

void rtype::network::FetchLobbiesDatagram::extractFetchLobbiesDatagram(uint64_t &userId)
{
    if (sizeof(RtypeOpCode) + sizeof(userId) > getSize()) {
        return;
    }
    userId = NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode)));
}
