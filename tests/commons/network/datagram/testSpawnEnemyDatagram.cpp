/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** testSpawnEnemyDatagram.cpp
*/

/* Created the 24/11/2019 at 18:33 by jbulteau */

#include <criterion/criterion.h>
#include "SpawnEnemyDatagram.hpp"

Test(spawnEnemyDatagram, create_datagram)
{
    rtype::network::SpawnEnemyDatagram datagram;

    datagram.createSpawnEnemyDatagram(12345, std::make_pair<float, float>(10.5, 20), "enemy");
    cr_expect_eq(NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint32_t))), 12345);
    cr_expect_eq(NTOHF(*reinterpret_cast<const uint32_t *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint32_t) + sizeof(uint64_t))), 10.5);
    cr_expect_eq(NTOHF(*reinterpret_cast<const uint32_t *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint32_t) + sizeof(uint64_t) + sizeof(uint32_t))), 20);
    cr_expect_str_eq(reinterpret_cast<const char *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint32_t) + sizeof(uint64_t) + sizeof(uint32_t) + sizeof(uint32_t)), "enemy");
}

Test(spawnEnemyDatagram, extract_datagram)
{
    auto opCode = rtype::network::RtypeDatagram::RtypeOpCodeSpawnEnemy;
    uint64_t enemyId = HTONLL(12345);
    uint32_t positionX = HTONF(10);
    uint32_t positionY = HTONF(20);
    std::string name = "enemy";
    uint32_t stringSize = HTONL(name.size());

    rtype::network::SpawnEnemyDatagram datagram;
    uint32_t size = HTONL(sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint64_t) + sizeof(uint32_t) * 2 + sizeof(char) * name.length());
    auto *buf = new unsigned char[size];
    std::memcpy(buf, &opCode, sizeof(rtype::network::RtypeDatagram::RtypeOpCode));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode), &stringSize, sizeof(uint32_t));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint32_t), &enemyId, sizeof(uint64_t));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint32_t) + sizeof(uint64_t), &positionX, sizeof(uint32_t));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint32_t) + sizeof(uint64_t) + sizeof(uint32_t), &positionY, sizeof(uint32_t));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint32_t) + sizeof(uint64_t) + sizeof(uint32_t) * 2, name.c_str(), sizeof(char) * name.length());
    datagram.setData(size, buf);

    uint64_t newEnemyId;
    std::pair<float, float> position;
    std::string newName;
    datagram.extractSpawnEnemyDatagram(newEnemyId, position, newName);
    cr_expect_eq(newEnemyId, 12345);
    cr_expect_eq(position.first, 10);
    cr_expect_eq(position.second, 20);
    cr_expect_str_eq(newName.c_str(), "enemy");

}
