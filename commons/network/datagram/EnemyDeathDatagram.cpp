/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** EnemyDeathDatagram.cpp
*/

/* Created the 24/11/2019 at 17:41 by jbulteau */

#include <cstring>
#include "EnemyDeathDatagram.hpp"

void rtype::network::EnemyDeathDatagram::createEnemyDeathDatagram(uint64_t enemyId)
{
    size_t size = sizeof(RtypeOpCode) + sizeof(enemyId);
    auto *buf = new unsigned char[size];
    RtypeOpCode opCode = RtypeOpCodeEnemyDeath;

    enemyId = HTONLL(enemyId);
    std::memcpy(buf, &opCode, sizeof(RtypeOpCode));
    std::memcpy(buf + sizeof(RtypeOpCode), &enemyId, sizeof(enemyId));
    setData(size, buf);
    delete [] buf;
}

void rtype::network::EnemyDeathDatagram::extractEnemyDeathDatagram(uint64_t &enemyId)
{
    if (sizeof(RtypeOpCode) + sizeof(enemyId) > getSize()) {
        return;
    }
    enemyId = NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode)));
}
