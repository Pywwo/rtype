/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** ConnectLobbyDatagram.cpp
*/

/* Created the 23/11/2019 at 19:38 by jules */

#include "ConnectLobbyDatagram.hpp"
#include <cstring>

void rtype::network::ConnectLobbyDatagram::createConnectLobbyDatagram(uint64_t userId, uint64_t lobbyId)
{
    size_t size = sizeof(RtypeOpCode) + sizeof(userId) + sizeof(lobbyId);
    auto *buf = new unsigned char[size];
    RtypeOpCode opCode = RtypeOpCodeConnectLobby;

    userId = HTONLL(userId);
    lobbyId = HTONLL(lobbyId);
    std::memcpy(buf, &opCode, sizeof(RtypeOpCode));
    std::memcpy(buf + sizeof(RtypeOpCode), &userId, sizeof(userId));
    std::memcpy(buf + sizeof(RtypeOpCode) + sizeof(userId), &lobbyId, sizeof(lobbyId));
    setData(size, buf);
    delete [] buf;
}

void rtype::network::ConnectLobbyDatagram::extractConnectLobbyDatagram(uint64_t &userId, uint64_t &lobbyId)
{
    if (sizeof(RtypeOpCode) + sizeof(userId) + sizeof(lobbyId) > getSize()) {
        return;
    }
    userId = NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode)));
    lobbyId = NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode) + sizeof(userId)));
}
