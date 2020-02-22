/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** RtypeDatagram.cpp
*/

/* Created the 20/11/2019 at 16:10 by jbulteau */

#include "RtypeDatagram.hpp"

rtype::network::RtypeDatagram::RtypeOpCode rtype::network::RtypeDatagram::getOpCode() const
{
    if (sizeof(RtypeOpCode) > getSize()) {
        return RtypeOpCodeNone;
    }
    return *reinterpret_cast<const RtypeOpCode *>(getData());
}
