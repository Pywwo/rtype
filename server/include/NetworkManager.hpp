/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** NetworkManager
*/

#ifndef RTYPE_NETWORKMANAGER_HPP
#define RTYPE_NETWORKMANAGER_HPP

#include <boost/asio.hpp>
#include "UdpSocket.hpp"
#include "../commons/network/datagram/Datagram.hpp"
#include <mutex>
#include <queue>
#include <map>
#include <vector>
#include "INetworkManager.hpp"

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
        class NetworkManager : public INetworkManager {
        public:
            /*!
             * @brief ctor
             */
            NetworkManager();
            /*!
             * @brief dtor
             */
            ~NetworkManager() override;

        public:
            void start(int port) override;
            void stop() override;

            void send(const Datagram &datagram) override;
            Datagram receive() override;

        private:

            /*!
             * @brief Function exceuted on the network thread
             * @param Networkmanager the container of the networkmanager
             */
            static void networkingThreadFunc(NetworkManager *manager);

        private:
            bool _isStarted; /*!< Is the network manager started */
            boost::asio::io_context _ioContext; /*!< Boost io context for the network manager */
            boost::asio::io_context::work *_worker; /*!< The work class is used to inform the io_context when work starts and finishes */
            std::thread _networkThread; /*!< The main network thread */
            UdpSocket _socket; /*!< The network server of the rtype server */
        };
    }
}

#endif // RTYPE_NETWORKMANAGER_HPP