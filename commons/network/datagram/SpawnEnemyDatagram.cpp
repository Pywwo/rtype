/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** SpawnEnemyDatagram.cpp
*/

/* Created the 24/11/2019 at 17:40 by jbulteau */

#include <cstring>
#include "SpawnEnemyDatagram.hpp"

void rtype::network::SpawnEnemyDatagram::createSpawnEnemyDatagram(uint64_t enemyId, const std::pair<float, float> &position, const std::string &name)
{
    size_t size = sizeof(RtypeOpCode) + sizeof(uint32_t) + sizeof(enemyId) + sizeof(uint32_t) * 2 + sizeof(char) * name.length();
    auto *buf = new unsigned char[size];
    RtypeOpCode opCode = RtypeOpCodeSpawnEnemy;
    uint32_t stringSize = HTONL(name.size());

    enemyId = HTONLL(enemyId);
    //HOST TO FLOAT WINDOWS COMPATIBLE WARNING WARNING WARNING WARNING WARNING
    uint32_t x = HTONF(position.first);
    uint32_t y = HTONF(position.second);
    std::memcpy(buf, &opCode, sizeof(RtypeOpCode));
    std::memcpy(buf + sizeof(RtypeOpCode), &stringSize, sizeof(stringSize));
    std::memcpy(buf + sizeof(RtypeOpCode) + sizeof(stringSize), &enemyId, sizeof(enemyId));
    std::memcpy(buf + sizeof(RtypeOpCode) + sizeof(stringSize) + sizeof(enemyId), &x, sizeof(x));
    std::memcpy(buf + sizeof(RtypeOpCode) + sizeof(stringSize) + sizeof(enemyId) + sizeof(x), &y, sizeof(y));
    std::memcpy(buf + sizeof(RtypeOpCode) + sizeof(stringSize) + sizeof(enemyId) + sizeof(x) + sizeof(y), name.c_str(), sizeof(char) * name.length());
    setData(size, buf);
    delete [] buf;
}

void rtype::network::SpawnEnemyDatagram::extractSpawnEnemyDatagram(uint64_t &enemyId, std::pair<float, float> &position, std::string &name)
{
    if (sizeof(RtypeOpCode) + sizeof(enemyId) + sizeof(uint32_t) * 2 + sizeof(char) > getSize()) {
        return;
    }
    uint32_t size = NTOHL(*reinterpret_cast<const uint32_t *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode)));
    enemyId = NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode) + sizeof(size)));
    //HOST TO FLOAT WINDOWS COMPATIBLE WARNING WARNING WARNING WARNING WARNING
    position.first = NTOHF(*reinterpret_cast<const uint32_t *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode) + sizeof(uint64_t) + sizeof(size)));
    position.second = NTOHF(*reinterpret_cast<const uint32_t *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode) + sizeof(uint64_t) + sizeof(size) + sizeof(uint32_t)));
    name.assign(reinterpret_cast<const char *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode) + sizeof(uint64_t) + sizeof(uint32_t) * 2 + sizeof(size)), size);
}
