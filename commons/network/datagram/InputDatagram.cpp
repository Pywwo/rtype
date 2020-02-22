/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** InputDatagram.cpp
*/

/* Created the 20/11/2019 at 15:09 by jbulteau */

#include <cstring>
#include "InputDatagram.hpp"

void rtype::network::InputDatagram::createInputDatagram(uint64_t userId, uint64_t lobbyId, RtypeGameKeys key, RtypeKeyState state)
{
    size_t size = sizeof(RtypeOpCode) + sizeof(userId) + sizeof(lobbyId) + sizeof(key) + sizeof(state);
    auto *buf = new unsigned char[size];
    RtypeOpCode opCode = RtypeOpCodeInput;

    userId = HTONLL(userId);
    lobbyId = HTONLL(lobbyId);
    std::memcpy(buf, &opCode, sizeof(RtypeOpCode));
    std::memcpy(buf + sizeof(RtypeOpCode), &userId, sizeof(userId));
    std::memcpy(buf + sizeof(RtypeOpCode) + sizeof(userId), &lobbyId, sizeof(lobbyId));
    std::memcpy(buf + sizeof(RtypeOpCode) + sizeof(userId) + sizeof(lobbyId), &key, sizeof(key));
    std::memcpy(buf + sizeof(RtypeOpCode) + sizeof(userId) + sizeof(lobbyId) + sizeof(key), &state, sizeof(state));
    setData(size, buf);
    delete [] buf;
}

void rtype::network::InputDatagram::extractInputDatagram(uint64_t &userId, uint64_t &lobbyId, RtypeGameKeys &key, RtypeKeyState &state)
{
    if (sizeof(RtypeOpCode) + sizeof(userId) + sizeof(lobbyId) + sizeof(key) + sizeof(state) > getSize()) {
        return;
    }
    userId = NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode)));
    lobbyId = NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode) + sizeof(userId)));
    key = *reinterpret_cast<const RtypeGameKeys *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode) + sizeof(userId) + sizeof(lobbyId));
    state = *reinterpret_cast<const RtypeKeyState *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode) + sizeof(userId) + sizeof(lobbyId) + sizeof(key));
}
