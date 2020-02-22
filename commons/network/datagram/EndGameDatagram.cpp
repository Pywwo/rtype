/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** EndGameDatagram.cpp
*/

/* Created the 20/11/2019 at 15:10 by jbulteau */

#include <cstring>
#include "EndGameDatagram.hpp"

void rtype::network::EndGameDatagram::createEndGameDatagram(const rtype::EndGameInfos &infos)
{
    size_t size = sizeof(RtypeOpCode) + sizeof(infos);
    auto *buf = new unsigned char[size];
    RtypeOpCode opCode = RtypeOpCodeEndGame;

    std::memcpy(buf, &opCode, sizeof(RtypeOpCode));
    std::memcpy(buf + sizeof(RtypeOpCode), &infos, sizeof(infos));
    setData(size, buf);
    delete [] buf;
}

void rtype::network::EndGameDatagram::extractEndGameDatagram(rtype::EndGameInfos &infos)
{
    if (sizeof(RtypeOpCode) + sizeof(infos) > getSize()) {
        return;
    }
    infos = *reinterpret_cast<const rtype::EndGameInfos *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode));
}
