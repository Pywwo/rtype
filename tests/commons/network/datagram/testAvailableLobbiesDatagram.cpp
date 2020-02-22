/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** testAvailableLobbiesDatagram.cpp
*/

/* Created the 20/11/2019 at 17:15 by jbulteau */

#include <criterion/criterion.h>
#include "AvailableLobbiesDatagram.hpp"

Test(availableLobbiesDatagram, create_datagram)
{
    rtype::network::AvailableLobbiesDatagram datagram;
    std::vector<rtype::Lobby> lobbies;
    rtype::Lobby lobby1 = {
            12345,
            {
                    {
                            54321,
                            "player1"
                    },
                    {
                            7890,
                            "player2"
                    }
            }
    };
    lobbies.push_back(lobby1);
    rtype::Lobby lobby2 = {
            67890,
            {
                    {
                            9876,
                            "player1"
                    },
                    {
                            1234,
                            "player2"
                    }
            }
    };
    lobbies.push_back(lobby2);

    datagram.createAvailableLobbiesDatagram(2, lobbies);

    size_t size = NTOHL(*reinterpret_cast<const uint32_t *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode)));
    std::vector<rtype::Lobby> newLobbies;
    for (size_t i = 0; i < size; i++) {
        newLobbies.push_back(*reinterpret_cast<const rtype::Lobby *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint32_t) + sizeof(rtype::Lobby) * i));
    }
    cr_expect_eq(size, 2);
    cr_expect_eq(newLobbies[0].id, 12345);
    cr_expect_eq(newLobbies[0].player[0].id, 54321);
    cr_expect_str_eq(newLobbies[0].player[0].name, "player1");
    cr_expect_eq(newLobbies[0].player[1].id, 7890);
    cr_expect_str_eq(newLobbies[1].player[1].name, "player2");
    cr_expect_eq(newLobbies[1].id, 67890);
    cr_expect_eq(newLobbies[1].player[0].id, 9876);
    cr_expect_str_eq(newLobbies[1].player[0].name, "player1");
    cr_expect_eq(newLobbies[1].player[1].id, 1234);
    cr_expect_str_eq(newLobbies[1].player[1].name, "player2");
}

Test(availableLobbiesDatagram, extract_datagram)
{
    auto opCode = rtype::network::RtypeDatagram::RtypeOpCodeCreateLobby;
    uint32_t nbLobby = HTONL(2);
    std::vector<rtype::Lobby> lobbies;
    rtype::Lobby lobby1 = {
            12345,
            {
                    {
                            54321,
                            "player1"
                    },
                    {
                            7890,
                            "player2"
                    }
            }
    };
    lobbies.push_back(lobby1);
    rtype::Lobby lobby2 = {
            67890,
            {
                    {
                            9876,
                            "player1"
                    },
                    {
                            1234,
                            "player2"
                    }
            }
    };
    lobbies.push_back(lobby2);

    rtype::network::AvailableLobbiesDatagram datagram;
    size_t size = sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint32_t) + sizeof(rtype::Lobby) * lobbies.size();
    auto *buf = new unsigned char [size];
    std::memcpy(buf, &opCode, sizeof(rtype::network::RtypeDatagram::RtypeOpCode));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode), &nbLobby, sizeof(uint32_t));
    size_t it = 0;
    for (auto &lobby : lobbies) {
        std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(uint32_t) + sizeof(rtype::Lobby) * it, &lobby, sizeof(rtype::Lobby));
        it++;
    }
    datagram.setData(size, buf);

    uint32_t newNbLobby = 0;
    std::vector<rtype::Lobby> newLobbies;
    datagram.extractAvailableLobbiesDatagram(newNbLobby, newLobbies);
    cr_expect_eq(newNbLobby, 2);
    cr_expect_eq(newLobbies[0].id, 12345);
    cr_expect_eq(newLobbies[0].player[0].id, 54321);
    cr_expect_str_eq(newLobbies[0].player[0].name, "player1");
    cr_expect_eq(newLobbies[0].player[1].id, 7890);
    cr_expect_str_eq(newLobbies[1].player[1].name, "player2");
    cr_expect_eq(newLobbies[1].id, 67890);
    cr_expect_eq(newLobbies[1].player[0].id, 9876);
    cr_expect_str_eq(newLobbies[1].player[0].name, "player1");
    cr_expect_eq(newLobbies[1].player[1].id, 1234);
    cr_expect_str_eq(newLobbies[1].player[1].name, "player2");
}