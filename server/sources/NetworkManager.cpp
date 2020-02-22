/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** NetworkManager
*/

#include "NetworkManager.hpp"

rtype::network::NetworkManager::NetworkManager()
    : _isStarted(false), _ioContext(), _worker(), _networkThread(), _socket(_ioContext)
{

}

rtype::network::NetworkManager::~NetworkManager()
{
    stop();
}

void rtype::network::NetworkManager::start(int port)
{
    if (_isStarted)
        return;
    _worker = new boost::asio::io_context::work(_ioContext);
    _networkThread = std::thread(&networkingThreadFunc, this);
    _isStarted = true;
    _socket.bind(port);
}

void rtype::network::NetworkManager::stop()
{
    if (!_isStarted)
        return;
    delete _worker;
    _networkThread.join();
    _isStarted = false;
    _socket.unbind();
}

void rtype::network::NetworkManager::networkingThreadFunc(rtype::network::NetworkManager *manager)
{
    manager->_ioContext.run();
}

void rtype::network::NetworkManager::send(const Datagram &datagram)
{
    _socket.send(datagram);
}

rtype::network::Datagram rtype::network::NetworkManager::receive()
{
    return _socket.receive();
}