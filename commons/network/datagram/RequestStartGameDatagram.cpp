/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** RequestStartGameDatagram.cpp
*/

/* Created the 23/11/2019 at 20:09 by jules */

#include "RequestStartGameDatagram.hpp"
#include <cstring>

void rtype::network::RequestStartGameDatagram::createRequestStartGameDatagram(uint64_t userId, uint64_t lobbyId)
{
    size_t size = sizeof(RtypeOpCode) + sizeof(userId) + sizeof(lobbyId);
    auto *buf = new unsigned char[size];
    RtypeOpCode opCode = RtypeOpCodeRequestStartGame;

    userId = HTONLL(userId);
    lobbyId = HTONLL(lobbyId);
    std::memcpy(buf, &opCode, sizeof(RtypeOpCode));
    std::memcpy(buf + sizeof(RtypeOpCode), &userId, sizeof(userId));
    std::memcpy(buf + sizeof(RtypeOpCode) + sizeof(userId), &lobbyId, sizeof(lobbyId));
    setData(size, buf);
    delete [] buf;
}

void rtype::network::RequestStartGameDatagram::extractRequestStartGameDatagram(uint64_t &userId, uint64_t &lobbyId)
{
    if (sizeof(RtypeOpCode) + sizeof(userId) + sizeof(lobbyId) > getSize()) {
        return;
    }
    userId = NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode)));
    lobbyId = NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode) + sizeof(userId)));
}
