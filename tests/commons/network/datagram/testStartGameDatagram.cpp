/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** testStartGameDatagram.cpp
*/

/* Created the 24/11/2019 at 15:43 by jbulteau */

#include <criterion/criterion.h>
#include "StartGameDatagram.hpp"

Test(startGameDatagram, create_datagram)
{
    rtype::network::StartGameDatagram datagram;
    rtype::ComponentInfos firstInfo = {
            "entity1",
            {10, 20},
            {5, 5}
    };
    rtype::ComponentInfos secondInfo = {
            "entity2",
            {30, 40},
            {2, 2}
    };
    std::vector<rtype::ComponentInfos> components;

    components.push_back(firstInfo);
    components.push_back(secondInfo);

    datagram.createStartGameDatagram(2, components);

    uint32_t size = NTOHL(*reinterpret_cast<const uint32_t *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode)));
    std::vector<rtype::ComponentInfos> newComponents;
    for (uint32_t i = 0; i < size; i++) {
        newComponents.push_back(*reinterpret_cast<const rtype::ComponentInfos *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint32_t) + sizeof(rtype::ComponentInfos) * i));
    }
    cr_expect_eq(size, 2);
    cr_expect_str_eq(newComponents[0].entityName, "entity1");
    cr_expect_eq(newComponents[0].position.first, 10);
    cr_expect_eq(newComponents[0].position.second, 20);
    cr_expect_eq(newComponents[0].velocity.first, 5);
    cr_expect_str_eq(newComponents[1].entityName, "entity2");
    cr_expect_eq(newComponents[1].position.first, 30);
    cr_expect_eq(newComponents[1].position.second, 40);
    cr_expect_eq(newComponents[1].velocity.first, 2);
}

Test(startGameDatagram, extract_datagram)
{
    auto opCode = rtype::network::RtypeDatagram::RtypeOpCodeStartGame;
    uint32_t nbComponents = HTONL(2);
    std::vector<rtype::ComponentInfos> components;
    rtype::ComponentInfos firstInfo = {
            "entity1",
            {10, 20},
            {5, 5}
    };
    rtype::ComponentInfos secondInfo = {
            "entity2",
            {30, 40},
            {2, 2}
    };

    components.push_back(firstInfo);
    components.push_back(secondInfo);

    rtype::network::StartGameDatagram datagram;
    uint32_t size = NTOHL(sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint32_t) + sizeof(rtype::ComponentInfos) * components.size());
    auto *buf = new unsigned char[size];
    std::memcpy(buf, &opCode, sizeof(rtype::network::RtypeDatagram::RtypeOpCode));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode), &nbComponents, sizeof(uint32_t));
    size_t it = 0;
    for (auto &component : components) {
        std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint32_t) + sizeof(rtype::ComponentInfos) * it, &component, sizeof(rtype::ComponentInfos));
        it++;
    }
    datagram.setData(size, buf);

    uint32_t newNbComponents;
    std::vector<rtype::ComponentInfos> newComponents;
    datagram.extractStartGameDatagram(newNbComponents, newComponents);
    cr_expect_eq(newNbComponents, 2);
    cr_expect_str_eq(newComponents[0].entityName, "entity1");
    cr_expect_eq(newComponents[0].position.first, 10);
    cr_expect_eq(newComponents[0].position.second, 20);
    cr_expect_eq(newComponents[0].velocity.first, 5);
    cr_expect_str_eq(newComponents[1].entityName, "entity2");
    cr_expect_eq(newComponents[1].position.first, 30);
    cr_expect_eq(newComponents[1].position.second, 40);
    cr_expect_eq(newComponents[1].velocity.first, 2);
}