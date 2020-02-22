/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** StartGameDatagram.cpp
*/

/* Created the 23/11/2019 at 20:06 by jules */

#include <cstring>
#include <iostream>
#include "StartGameDatagram.hpp"

void rtype::network::StartGameDatagram::createStartGameDatagram(uint32_t nbComponents, const std::vector<ComponentInfos> &components)
{
    size_t size = sizeof(RtypeOpCode) + sizeof(nbComponents) + sizeof(ComponentInfos) * nbComponents;
    auto *buf = new unsigned char[size];
    RtypeOpCode opCode = RtypeOpCodeStartGame;

    nbComponents = HTONL(nbComponents);
    std::memcpy(buf, &opCode, sizeof(RtypeOpCode));
    std::memcpy(buf + sizeof(RtypeOpCode), &nbComponents, sizeof(nbComponents));
    size_t it = 0;
    for (auto &component : components) {
        std::memcpy(buf + sizeof(RtypeOpCode) + sizeof(nbComponents) + sizeof(ComponentInfos) * it, &component, sizeof(ComponentInfos));
        it++;
    }
    setData(size, buf);
    delete [] buf;
}

void rtype::network::StartGameDatagram::extractStartGameDatagram(uint32_t &nbComponents, std::vector<ComponentInfos> &components)
{
    if (sizeof(RtypeOpCode) + sizeof(nbComponents) + sizeof(ComponentInfos) > getSize()) {
        return;
    }
    nbComponents = NTOHL(*reinterpret_cast<const uint32_t *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode)));
    for (size_t i = 0; i < nbComponents; i++) {
        components.push_back(*reinterpret_cast<const ComponentInfos *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode) + sizeof(nbComponents) + sizeof(ComponentInfos) * i));
    }
}
