/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** testDatagram.cpp
*/

/* Created the 20/11/2019 at 10:49 by jbulteau */

#include <criterion/criterion.h>
#include "Datagram.hpp"

Test(datagram, empty_constructor)
{
    rtype::network::Datagram datagram;

    cr_expect_str_empty(datagram.getHostInfos().host.c_str());
    cr_expect_eq(datagram.getHostInfos().port, 0);
    cr_expect_null(datagram.getData());
}

Test(datagram, empty_data)
{
    rtype::network::Datagram datagram({"127.0.0.1", 8080});

    cr_expect_str_eq(datagram.getHostInfos().host.c_str(), "127.0.0.1");
    cr_expect_eq(datagram.getHostInfos().port, 8080);
    cr_expect_null(datagram.getData());
}

Test(datagram, empty_host)
{
    char *str = "Hello World";
    size_t size = sizeof(char) * strlen(str);
    rtype::network::Datagram datagram(size, str);

    cr_expect_str_empty(datagram.getHostInfos().host.c_str());
    cr_expect_eq(datagram.getHostInfos().port, 0);
    cr_expect_str_eq(static_cast<const char *>(datagram.getData()), "Hello World");
}

Test(datagram, all_infos)
{
    char *str = "Hello World";
    size_t size = sizeof(char) * strlen(str);
    rtype::network::Datagram datagram({"127.0.0.1", 8080}, size, str);

    cr_expect_str_eq(datagram.getHostInfos().host.c_str(), "127.0.0.1");
    cr_expect_eq(datagram.getHostInfos().port, 8080);
    cr_expect_str_eq(static_cast<const char *>(datagram.getData()), "Hello World");
}

Test(datagram, set_hostinfos)
{
    rtype::network::Datagram datagram;

    datagram.setHostInfos({"127.0.0.1", 8080});
    cr_expect_str_eq(datagram.getHostInfos().host.c_str(), "127.0.0.1");
    cr_expect_eq(datagram.getHostInfos().port, 8080);
    cr_expect_null(datagram.getData());
}

Test(datagram, set_data)
{
    char *str = "Hello World";
    size_t size = sizeof(char) * strlen(str);
    rtype::network::Datagram datagram;

    datagram.setData(size, str);
    cr_expect_str_empty(datagram.getHostInfos().host.c_str());
    cr_expect_eq(datagram.getHostInfos().port, 0);
    cr_expect_str_eq(static_cast<const char *>(datagram.getData()), "Hello World");
}