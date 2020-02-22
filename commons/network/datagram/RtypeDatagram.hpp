/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** RtypeDatagram.hpp
*/

/* Created the 20/11/2019 at 16:10 by jbulteau */

#ifndef RTYPE_RTYPEDATAGRAM_HPP
#define RTYPE_RTYPEDATAGRAM_HPP

#include "Datagram.hpp"

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
    #pragma  comment(lib, "ws2_32.lib")

    #include <ws2tcpip.h>
    #include <winsock.h>
    #include <winsock2.h>

    #define HTONS(x) (htons(x))
    #define NTOHS(x) (ntohs(x))

    #define HTONF(x) (htonf(x))
    #define NTOHF(x) (ntohf(x))

    #define HTONL(x) (htonl(x))
    #define NTOHL(x) (ntohl(x))

    #define HTONLL(x) (htonll(x))
    #define NTOHLL(x) (ntohll(x))
#else
    #include <sys/types.h>
    #include <netinet/in.h>

    #define HTONS(x) (htons(x))
    #define NTOHS(x) (ntohs(x))

    #define HTONF(x) ((x < 0) ? ((((((uint32_t)(-x)) & 0x7fff) << 16) | (1 << 31)) | (uint32_t)((((-x) - (int)(-x)) * 65536.0f)) & 0xffff) : ((((((uint32_t)x) & 0x7fff) << 16) | (0 << 31)) | (uint32_t)(((x - (int)x) * 65536.0f)) & 0xffff))
    #define NTOHF(x) ((((x >> 31) & 0x1) == 0x1) ? -((((x >> 16) & 0x7fff)) + (x & 0xffff) / 65536.0f) : ((((x >> 16) & 0x7fff)) + (x & 0xffff) / 65536.0f))

    #define HTONL(x) (htonl(x))
    #define NTOHL(x) (ntohl(x))

    #define HTONLL(x) ((1==htonl(1)) ? (x) : (((uint64_t)htonl((x) & 0xFFFFFFFFUL)) << 32) | htonl((uint32_t)((x) >> 32)))
    #define NTOHLL(x) ((1==ntohl(1)) ? (x) : (((uint64_t)ntohl((x) & 0xFFFFFFFFUL)) << 32) | ntohl((uint32_t)((x) >> 32)))
#endif

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
         * @class RtypeDatagram
         * @brief Datagram class for Rtype, automatically fill datagram with Rtype command opcode
         */
        class RtypeDatagram : public Datagram {
        public:
            enum RtypeOpCode {
                RtypeOpCodeNone,
                RtypeOpCodeBinary = 100,
                RtypeOpCodeConnectServer = 120,
                RtypeOpCodeLobbyInfos = 210,
                RtypeOpCodeAvailableLobbies = 211,
                RtypeOpCodeCreateLobby = 220,
                RtypeOpCodeFetchLobbies = 221,
                RtypeOpCodeConnectLobby = 222,
                RtypeOpCodeLeaveLobby = 223,
                RtypeOpCodeStartGame = 310,
                RtypeOpCodePlayerDeath = 311,
                RtypeOpCodeTriggerBonus = 312,
                RtypeOpCodeSpawnEnemy = 313,
                RtypeOpCodeEnemyDeath = 314,
                RtypeOpCodeEndGame = 315,
                RtypeOpCodeDeletePlayer = 316,
                RtypeOpCodeInput = 320,
                RtypeOpCodeRequestStartGame = 321,
                RtypeOpCodeLeaveGame = 322,
                RtypeOpCodeUpdateComponents = 410
            };

        public:
            /*!
             * @brief ctor
             */
            RtypeDatagram() = default;
            /*!
             * @brief dtor
             */
            ~RtypeDatagram() = default;

            /*!
             * @brief Return the opcode contained in the datagram
             * @return An enum value for opcode
             */
            RtypeOpCode getOpCode() const;
        };
    }
}

#endif //RTYPE_RTYPEDATAGRAM_HPP
