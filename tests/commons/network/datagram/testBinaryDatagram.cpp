/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** testBinaryDatagram.cpp
*/

/* Created the 20/11/2019 at 22:45 by jbulteau */

#include <criterion/criterion.h>
#include "BinaryDatagram.hpp"

Test(binaryDatagram, create_datagram)
{
    rtype::network::BinaryDatagram datagram;

    datagram.createBinaryDatagram(true, "Hello World");
    cr_expect_eq(*reinterpret_cast<const bool *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode)), true);
    cr_expect_str_eq(reinterpret_cast<const char *>(reinterpret_cast<intptr_t>(datagram.getData()) + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(bool)), "Hello World");
}

Test(binaryDatagram, extract_datagram)
{
    auto opCode = rtype::network::RtypeDatagram::RtypeOpCodeBinary;
    bool value = true;
    std::string description = "Hello World";
    rtype::network::BinaryDatagram datagram;
    size_t size = sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(long) + sizeof(char) * description.size();
    auto *buf = new unsigned char [size];
    std::memcpy(buf, &opCode, sizeof(rtype::network::RtypeDatagram::RtypeOpCode));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode), &value, sizeof(bool));
    std::memcpy(buf + sizeof(rtype::network::RtypeDatagram::RtypeOpCode) + sizeof(bool), description.c_str(), sizeof(char) * description.size());
    datagram.setData(size, buf);

    bool newValue;
    std::string newDescription;
    datagram.extractBinaryDatagram(newValue, newDescription);
    cr_expect_eq(newValue, true);
    cr_expect_str_eq(newDescription.c_str(), "Hello World");
}