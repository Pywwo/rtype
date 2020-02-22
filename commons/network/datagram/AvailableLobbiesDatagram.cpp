/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** AvailableLobbiesDatagram.cpp
*/

/* Created the 20/11/2019 at 15:08 by jbulteau */

#include <cstring>
#include "AvailableLobbiesDatagram.hpp"

void rtype::network::AvailableLobbiesDatagram::createAvailableLobbiesDatagram(uint32_t nbLobby, const std::vector<rtype::Lobby> &lobbies)
{
    size_t size = sizeof(RtypeOpCode) + sizeof(uint32_t) + sizeof(Lobby) * nbLobby;
    auto *buf = new unsigned char[size];
    RtypeOpCode opCode = RtypeOpCodeAvailableLobbies;

    nbLobby = HTONL(nbLobby);
    std::memcpy(buf, &opCode, sizeof(RtypeOpCode));
    std::memcpy(buf + sizeof(RtypeOpCode), &nbLobby, sizeof(nbLobby));
    size_t it = 0;
    for (auto &lobby : lobbies) {
        std::memcpy(buf + sizeof(RtypeOpCode) + sizeof(nbLobby) + sizeof(Lobby) * it, &lobby, sizeof(Lobby));
        it++;
    }
    setData(size, buf);
    delete [] buf;
}

void rtype::network::AvailableLobbiesDatagram::extractAvailableLobbiesDatagram(uint32_t &nbLobby, std::vector<rtype::Lobby> &lobbies)
{
    if (sizeof(RtypeOpCode) + sizeof(uint32_t) + sizeof(Lobby) > getSize()) {
        return;
    }
    nbLobby = NTOHL(*reinterpret_cast<const uint32_t *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode)));
    for (size_t i = 0; i < nbLobby; i++) {
        lobbies.push_back(*reinterpret_cast<const Lobby *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode) + sizeof(nbLobby) + sizeof(Lobby) * i));
    }
}
