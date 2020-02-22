/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** testKeyPressedDatagram.cpp
*/

/* Created the 20/11/2019 at 18:45 by jbulteau */

#include <criterion/criterion.h>
#include "InputDatagram.hpp"

Test(inputDatagram, create_datagram)
{
    rtype::network::InputDatagram datagram;

    datagram.createInputDatagram(12345, 54321, rtype::KEY_SHOOT, rtype::KEY_PRESSED);
    auto data = datagram.getData();
    cr_expect_eq(NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(data) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode))), 12345);
    cr_expect_eq(NTOHLL(*reinterpret_cast<const uint64_t *>(reinterpret_cast<intptr_t>(data) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(long))), 54321);
    cr_expect_eq(*reinterpret_cast<const rtype::RtypeGameKeys *>(reinterpret_cast<intptr_t>(data) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(long) + sizeof(long)), rtype::KEY_SHOOT);
    cr_expect_eq(*reinterpret_cast<const rtype::RtypeGameKeys *>(reinterpret_cast<intptr_t>(data) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(long) + sizeof(long) + sizeof(rtype::RtypeGameKeys)), rtype::KEY_PRESSED);
}

Test(inputDatagram, extract_datagram)
{
    auto opCode = rtype::network::RtypeDatagram::RtypeOpCodeInput;
    uint64_t userId = HTONLL(12345);
    uint64_t lobbyId = HTONLL(54321);
    auto key = rtype::KEY_SHOOT;
    auto state = rtype::KEY_PRESSED;
    rtype::network::InputDatagram datagram;
    size_t size = sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(long) * 2 + sizeof(rtype::RtypeGameKeys) + sizeof(rtype::RtypeKeyState);
    auto *buf = new unsigned char [size];
    std::memcpy(buf, &opCode, sizeof(rtype::network::RtypeDatagram::RtypeOpCode));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode), &userId, sizeof(userId));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(userId), &lobbyId, sizeof(lobbyId));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(userId) + sizeof(lobbyId), &key, sizeof(key));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(userId) + sizeof(lobbyId) + sizeof(key), &state, sizeof(state));
    datagram.setData(size, buf);

    uint64_t newUserId;
    uint64_t newLobbyId;
    rtype::RtypeGameKeys newKey;
    rtype::RtypeKeyState newState;
    datagram.extractInputDatagram(newUserId, newLobbyId, newKey, newState);
    cr_expect_eq(newUserId, 12345);
    cr_expect_eq(newLobbyId, 54321);
    cr_expect_eq(newKey, rtype::KEY_SHOOT);
    cr_expect_eq(newState, rtype::KEY_PRESSED);
}