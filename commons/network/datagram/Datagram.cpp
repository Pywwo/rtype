/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** datagram.cpp
*/

/* Created the 18/11/2019 at 16:38 by jbulteau */

#include "Datagram.hpp"
#include <cstring>

rtype::network::Datagram::Datagram()
    : _hostInfos({"", 0})
    , _size(0)
    , _data(nullptr)
{}

rtype::network::Datagram::Datagram(const rtype::network::HostInfos &hostInfos)
    : _hostInfos(hostInfos)
    , _size(0)
    , _data(nullptr)
{}

rtype::network::Datagram::Datagram(size_t size, void *data)
    : _hostInfos({"", 0})
    , _size(size)
{
    _data = new unsigned char [_size];
    std::memcpy(_data, data, _size);
}

rtype::network::Datagram::Datagram(const HostInfos &hostInfos, size_t size, void *data)
    : _hostInfos(hostInfos)
    , _size(size)
{
    _data = new unsigned char [_size];
    std::memcpy(_data, data, _size);
}

rtype::network::Datagram::Datagram(const rtype::network::Datagram &datagram)
    : _hostInfos(datagram.getHostInfos())
    , _size(datagram.getSize())
{
    _data = new unsigned char [_size];
    std::memcpy(_data, datagram.getData(), _size);
}

rtype::network::Datagram::~Datagram()
{
    clear();
}

void rtype::network::Datagram::setHostInfos(const HostInfos &hostInfos)
{
    _hostInfos = hostInfos;
}

const rtype::network::HostInfos &rtype::network::Datagram::getHostInfos() const
{
    return _hostInfos;
}

void rtype::network::Datagram::setData(size_t size, void *data)
{
    _size = size;
    _data = new unsigned char [_size];
    std::memcpy(_data, data, _size);
}

size_t rtype::network::Datagram::getSize() const
{
    return _size;
}

const void *rtype::network::Datagram::getData() const
{
    return _data;
}

void rtype::network::Datagram::clear()
{
    _hostInfos = {"", 0};
    _size = 0;
    if (_data && _size) {
        delete [] reinterpret_cast<unsigned char *>(_data);
    }
    _data = nullptr;
}
