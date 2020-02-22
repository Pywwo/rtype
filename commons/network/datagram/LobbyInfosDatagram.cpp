/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** LobbyInfosDatagram.cpp
*/

/* Created the 23/11/2019 at 19:38 by jules */

#include "LobbyInfosDatagram.hpp"
#include <cstring>

void rtype::network::LobbyInfosDatagram::createLobbyInfosDatagram(const rtype::Lobby &lobby)
{
    size_t size = sizeof(RtypeOpCode) + sizeof(lobby);
    auto *buf = new unsigned char[size];
    RtypeOpCode opCode = RtypeOpCodeLobbyInfos;

    std::memcpy(buf, &opCode, sizeof(RtypeOpCode));
    std::memcpy(buf + sizeof(RtypeOpCode), &lobby, sizeof(lobby));
    setData(size, buf);
    delete [] buf;
}

void rtype::network::LobbyInfosDatagram::extractLobbyInfosDatagram(rtype::Lobby &lobby)
{
    if (sizeof(RtypeOpCode) + sizeof(lobby) > getSize()) {
        return;
    }
    lobby = *reinterpret_cast<const Lobby *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode));
}
