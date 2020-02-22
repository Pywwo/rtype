/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** testLobbyInfosDatagram.cpp
*/

/* Created the 24/11/2019 at 15:42 by jbulteau */

#include <criterion/criterion.h>
#include "LobbyInfosDatagram.hpp"

Test(lobbyInfosDatagram, create_datagram)
{
    rtype::network::LobbyInfosDatagram datagram;
    rtype::Lobby lobby = {
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

    datagram.createLobbyInfosDatagram(lobby);

    rtype::Lobby newLobby = *reinterpret_cast<const rtype::Lobby *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode));
    cr_expect_eq(newLobby.id, 12345);
    cr_expect_eq(newLobby.player[0].id, 54321);
    cr_expect_str_eq(newLobby.player[0].name, "player1");
    cr_expect_eq(newLobby.player[1].id, 7890);
    cr_expect_str_eq(newLobby.player[1].name, "player2");
}

Test(lobbyInfosDatagram, extract_datagram)
{
    auto opCode = rtype::network::RtypeDatagram::RtypeOpCodeLobbyInfos;
    rtype::Lobby lobby = {
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

    rtype::network::LobbyInfosDatagram datagram;
    size_t size = sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(rtype::Lobby);
    auto *buf = new unsigned char[size];
    std::memcpy(buf, &opCode, sizeof(rtype::network::RtypeDatagram::RtypeOpCode));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode), &lobby, sizeof(rtype::Lobby));
    datagram.setData(size, buf);

    rtype::Lobby newLobby;
    datagram.extractLobbyInfosDatagram(newLobby);
    cr_expect_eq(newLobby.id, 12345);
    cr_expect_eq(newLobby.player[0].id, 54321);
    cr_expect_str_eq(newLobby.player[0].name, "player1");
    cr_expect_eq(newLobby.player[1].id, 7890);
    cr_expect_str_eq(newLobby.player[1].name, "player2");
}