/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** DeletePlayerDatagram.cpp
*/

/* Created the 29/11/2019 at 18:55 by acarlier */

#include <cstring>
#include "DeletePlayerDatagram.hpp"

void rtype::network::DeletePlayerDatagram::createDeletePlayerDatagram(const std::string &playerName)
{
    size_t size = sizeof(RtypeOpCode) + sizeof(uint32_t) + sizeof(char) * playerName.size();
    auto *buf = new unsigned char[size];
    RtypeOpCode opCode = RtypeOpCodeDeletePlayer;
    uint32_t stringSize = HTONL(playerName.size());

    std::memcpy(buf, &opCode, sizeof(RtypeOpCode));
    std::memcpy(buf + sizeof(RtypeOpCode), &stringSize, sizeof(stringSize));
    std::memcpy(buf + sizeof(RtypeOpCode) + sizeof(stringSize), playerName.c_str(), sizeof(char) * playerName.size());
    setData(size, buf);
    delete [] buf;
}

void rtype::network::DeletePlayerDatagram::extractDeletePlayerDatagram(std::string &playerName)
{
    if (sizeof(RtypeOpCode) + sizeof(char) > getSize()) {
        return;
    }
    uint32_t size = NTOHL(*reinterpret_cast<const uint32_t *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode)));
    playerName.assign(reinterpret_cast<const char *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode) + sizeof(size)), size);
}