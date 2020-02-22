/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** BinaryDatagram.cpp
*/

/* Created the 20/11/2019 at 15:10 by jbulteau */

#include <cstring>
#include "BinaryDatagram.hpp"

void rtype::network::BinaryDatagram::createBinaryDatagram(bool value, const std::string &description)
{
    size_t size = sizeof(RtypeOpCode) + sizeof(value) + sizeof(char) * description.size();
    auto *buf = new unsigned char[size];
    RtypeOpCode opCode = RtypeOpCodeBinary;

    std::memcpy(buf, &opCode, sizeof(RtypeOpCode));
    std::memcpy(buf + sizeof(RtypeOpCode), &value, sizeof(value));
    std::memcpy(buf + sizeof(RtypeOpCode) + sizeof(value), description.c_str(), sizeof(char) * description.size());
    setData(size, buf);
    delete [] buf;
}

void rtype::network::BinaryDatagram::extractBinaryDatagram(bool &value, std::string &description)
{
    if (sizeof(RtypeOpCode) + sizeof(value) + sizeof(char) > getSize()) {
        return;
    }
    value = *reinterpret_cast<const bool *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode));
    description = reinterpret_cast<const char *>(reinterpret_cast<intptr_t>(getData()) + sizeof(RtypeOpCode) + sizeof(value));
}
