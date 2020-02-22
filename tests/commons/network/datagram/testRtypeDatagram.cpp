/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** testRtypeDatagram.cpp
*/

/* Created the 24/11/2019 at 15:47 by jbulteau */

#include <criterion/criterion.h>
#include "RtypeDatagram.hpp"
#include "BinaryDatagram.hpp"

Test(rtypeDatagram, get_op_code)
{
    rtype::network::RtypeDatagram datagram;
    (*reinterpret_cast<rtype::network::BinaryDatagram *>(&datagram)).createBinaryDatagram(true, "");
    cr_expect_eq(datagram.getOpCode(), rtype::network::RtypeDatagram::RtypeOpCodeBinary);
}