/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** testEndGameDatagram.cpp
*/

/* Created the 20/11/2019 at 18:18 by jbulteau */

#include <criterion/criterion.h>
#include "EndGameDatagram.hpp"

Test(endGameDatagram, create_datagram)
{
    rtype::network::EndGameDatagram datagram;
    rtype::EndGameInfos infos = {
            12345
    };

    datagram.createEndGameDatagram(infos);

    rtype::EndGameInfos newInfos = *reinterpret_cast<const rtype::EndGameInfos *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode));
    cr_expect_eq(newInfos.score, 12345);
}

Test(endGameDatagram, extract_datagram)
{
    auto opCode = rtype::network::RtypeDatagram::RtypeOpCodeEndGame;
    rtype::EndGameInfos infos = {
            12345
    };

    rtype::network::EndGameDatagram datagram;
    size_t size = sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(rtype::EndGameInfos);
    auto *buf = new unsigned char [size];
    std::memcpy(buf, &opCode, sizeof(rtype::network::RtypeDatagram::RtypeOpCode));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode), &infos, sizeof(rtype::EndGameInfos));
    datagram.setData(size, buf);

    rtype::EndGameInfos newInfos;
    datagram.extractEndGameDatagram(newInfos);
    cr_expect_eq(newInfos.score, 12345);
}