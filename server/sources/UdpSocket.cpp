/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** UdpSocket.cpp
*/

#include "UdpSocket.hpp"

rtype::network::UdpSocket::UdpSocket(boost::asio::io_context &context)
: _socket(context), _context(context)
{
}

rtype::network::UdpSocket::~UdpSocket()
{
    unbind();
}

void rtype::network::UdpSocket::bind(int port)
{
    if (!_socket.is_open()) {
        try {
            _socket.open(boost::asio::ip::udp::v4());
        }
        catch (boost::system::system_error &error) {
            throw NetworkException("Error when opening socket");
        }
    }
    try {
        _socket.bind(boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port));
    }
    catch (boost::system::system_error &error) {
        throw NetworkException("Error when binding socket");
    }
    prepareReceiving();
}

rtype::network::Datagram rtype::network::UdpSocket::receive()
{
    Datagram ret;

    if (_queueDatagram.isEmpty()) {
        ret.setData(0, nullptr);
        return ret;
    }
    ret = _queueDatagram.front();
    _queueDatagram.pop();
    return ret;
}

bool rtype::network::UdpSocket::isQueueEmpty()
{
    return _queueDatagram.isEmpty();
}

void rtype::network::UdpSocket::unbind()
{
    try {
        _socket.cancel();
        _socket.close();
    }
    catch (boost::system::system_error &error) {
        throw NetworkException("Error when closing socket");
    }
}

void rtype::network::UdpSocket::prepareReceiving()
{
    std::shared_ptr<boost::asio::ip::udp::endpoint> endpoint(new boost::asio::ip::udp::endpoint());
    std::shared_ptr<std::array<char, numberMaxDatagram>> readingPointer(new std::array<char, numberMaxDatagram>());

    _socket.async_receive_from(
        boost::asio::buffer(*readingPointer),
        *endpoint,
        std::bind(
            &rtype::network::UdpSocket::receiveCallback,
            this,
            readingPointer,
            endpoint,
            std::placeholders::_1,
            std::placeholders::_2
        )
    );
}

void rtype::network::UdpSocket::receiveCallback(const std::shared_ptr<std::array<char, numberMaxDatagram>> &readingPointer, const std::shared_ptr<boost::asio::ip::udp::endpoint> &endpoint, const std::error_code &errorCode, std::size_t size)
{
    if (!errorCode) {
        HostInfos sender;

        sender.host = endpoint->address().to_string();
        sender.port = endpoint->port();
        Datagram toPush(sender);
        toPush.setData(size, &readingPointer->front());
        _queueDatagram.push_back(toPush);
        prepareReceiving();
    }
}

void rtype::network::UdpSocket::send(const Datagram &datagram)
{
    auto infos = datagram.getHostInfos();
    boost::asio::ip::udp::resolver resolver(_context);
    auto address = resolver.resolve(infos.host, std::to_string(infos.port))->endpoint();
    std::shared_ptr<Datagram> message(new Datagram(datagram.getHostInfos()));
    auto data = const_cast<void *>(datagram.getData());

    message->setData(datagram.getSize(), data);
    _socket.async_send_to(
        boost::asio::buffer(datagram.getData(), datagram.getSize()),
        address,
        std::bind(
            &rtype::network::UdpSocket::sendErrorHandler,
            this,
            message,
            std::placeholders::_1,
            std::placeholders::_2
        )
    );
}

void rtype::network::UdpSocket::sendErrorHandler(const std::shared_ptr<Datagram> &message, const std::error_code &errorCode, std::size_t size)
{
    if (errorCode) {
        throw NetworkException("Error when sending package.");
    }
}

int rtype::network::UdpSocket::getPort() const
{
    return _socket.local_endpoint().port();
}

std::string rtype::network::UdpSocket::getAddress() const
{
    return _socket.local_endpoint().address().to_string();
}