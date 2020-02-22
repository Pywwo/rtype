/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** UpdateComponentsDatagram.cpp
*/

/* Created the 24/11/2019 at 17:41 by jbulteau */

#include <cstring>
#include "UpdateComponentsDatagram.hpp"

void rtype::network::UpdateComponentsDatagram::createUpdateComponentDatagram(uint32_t nbComponents, const std::vector<ComponentInfos> &components)
{
    size_t size = sizeof(RtypeOpCode) + sizeof(nbComponents) + sizeof(ComponentInfos) * nbComponents;
    auto *buf = new unsigned char[size];
    RtypeOpCode opCode = RtypeOpCodeUpdateComponents;

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

void rtype::network::UpdateComponentsDatagram::extractUpdateComponentDatagram(uint32_t &nbComponents, std::vector<ComponentInfos> &components)
{
    if (sizeof(RtypeOpCode) + sizeof(nbComponents) + sizeof(ComponentInfos) > getSize()) {
        return;
    }
    nbComponents = NTOHL(*reinterpret_cast<const size_t *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode)));
    for (size_t i = 0; i < nbComponents; i++) {
        components.push_back(*reinterpret_cast<const ComponentInfos *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode) + sizeof(nbComponents) + sizeof(ComponentInfos) * i));
    }
}
