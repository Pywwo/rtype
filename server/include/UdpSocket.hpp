/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** UdpSocket.hpp
*/

#ifndef RTYPE_UDPSOCKET_HPP
#define RTYPE_UDPSOCKET_HPP

#include <boost/asio.hpp>
#include "network/HostInfos.hpp"
#include "IUdpSocket.hpp"
#include "ThreadSafeQueue.hpp"
#include "network/datagram/Datagram.hpp"
#include "RtypeException.hpp"

/*!
 * @namespace rtype
 * @brief Main namespace for all rtype project
 */
namespace rtype {
    /*!
    * @namespace rtype::network
    * @brief Main namespace for all networking
    */
    namespace network {
        /*!
         * @const_size numberMaxDatagram
         * @brief maximun number of data readable (in byte size)
         */
        static constexpr size_t numberMaxDatagram = 2048;
        /*!
         * @class UdpSocket
         * @brief Class that encapsulate boost::asio udp socket.
         */
        class UdpSocket : public IUdpSocket {
        public:
            /*!
             * Constructor of the UdpSocket class
             * @param context a boost::asio::io_context to set to the socket
             */
            explicit UdpSocket(boost::asio::io_context &context);
            ~UdpSocket() override;
            void bind(int port) override;
            void unbind() override;
            void send(const Datagram &datagram) override;
            [[nodiscard]] int getPort() const override;
            [[nodiscard]] std::string getAddress() const override;
        public:
            /*!
             * return a Datagram of the first element in queue, filled when you read data on the socket.
             * @return a Datagram
             */
            Datagram receive();
            /*!
             * return true if the queue is empty, otherwise false
             * @return a boolean
             */
            bool isQueueEmpty();
        private:
            /*!
             * Callback method called when you send data
             *
             * @param message shared ptr to the sended Datagram
             * @param errorCode the code of the error (if one)
             * @param size the size of the data sended
             */
            void sendErrorHandler(const std::shared_ptr<Datagram> &message, const std::error_code &errorCode, std::size_t size);
            /*!
             * Method called to initialize the receiving of data
             */
            void prepareReceiving();
            /*!
             * callback method called when you read something on the socket. Stock the Datagram in the queue
             * @param readingPointer a pointer to the readed buffer
             * @param endpoint a pointer to the endpoint
             * @param errorCode the code of the error (if one)
             * @param size the size of the data sended
             */
            void receiveCallback(const std::shared_ptr<std::array<char, numberMaxDatagram>> &readingPointer, const std::shared_ptr<boost::asio::ip::udp::endpoint> &endpoint, const std::error_code &errorCode, std::size_t size);
        private:
            boost::asio::ip::udp::socket _socket;
            boost::asio::io_context &_context;
            ThreadSafeQueue<Datagram> _queueDatagram;
        };
    }
}
#endif