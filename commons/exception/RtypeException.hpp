/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** RTYPEexception.hpp
*/

/* Created the 21/11/2019 at 17:49 by acarlier */

#ifndef RTYPE_RTYPEEXCEPTION_HPP
#define RTYPE_RTYPEEXCEPTION_HPP

#include <exception>
#include <string>

/*!
 * @namespace rtype
 * @brief Main namespace for all rtype project
 */
namespace rtype {
    /*!
     * @class RtypeException
     * @brief Class for every rtype exception that inherit from std::exception and act like a standard exception
     */
    class RtypeException : public std::exception {
    public:
        explicit RtypeException(const std::string &error) : _error(error) {};
        const char *what() const noexcept override {
            return _error.c_str();
        }
    protected:
        std::string _error;
    };

    /*!
     * @class NetworkException
     * @brief Class for every network related exception, inherit from RtypeException
     */
    class NetworkException : public RtypeException {
    public:
        explicit NetworkException(const std::string &error) : RtypeException(error) {};
    };

    /*!
     * @class ComponentException
     * @brief Class for every component related exception, inherit from RtypeException
     */
    class ComponentException : public RtypeException {
    public:
        explicit ComponentException(const std::string &error) : RtypeException(error) {};
    };

    /*!
     * @class WorldException
     * @brief Class for every world related exception, inherit from RtypeException
     */
    class WorldException : public RtypeException {
    public:
        explicit WorldException(const std::string &error) : RtypeException(error) {};
    };

    /*!
     * @class ThreadException
     * @brief Class for every thread related exception, inherit from RtypeException
     */
    class ThreadException : public RtypeException {
    public:
        explicit ThreadException(const std::string &error) : RtypeException(error) {};
    };

    /*!
     * @class LobbyException
     * @brief Class for every lobby related exception, inherit from RtypeException
     */
    class LobbyException : public RtypeException {
    public:
        explicit LobbyException(const std::string &error) : RtypeException(error) {};
    };

    /*!
     * @class LobbyFullException
     * @brief Exception thrown when a lobby is full and someone try to join it, inherit from LobbyException
     */
    class LobbyFullException : public LobbyException {
    public:
        explicit LobbyFullException(const std::string &error) : LobbyException(error) {};
    };

    /*!
     * @class AlreadyInLobbyException
     * @brief Exception thrown when a player try to join a lobby when already in a lobby, inherit from LobbyException
     */
    class AlreadyInLobbyException : public LobbyException {
    public:
        explicit AlreadyInLobbyException(const std::string &error) : LobbyException(error) {};
    };

    /*!
     * @class NotInLobbyException
     * @brief Exception thrown when a player try to leave a lobby he is not part of, inherit from LobbyException
     */
    class NotInLobbyException : public LobbyException {
    public:
        explicit NotInLobbyException(const std::string &error) : LobbyException(error) {};
    };

    /*!
     * @class NonExistentLobbyException
     * @brief Exception thrown when a player try to join a lobby that does not exist, inherit from LobbyException
     */
    class NonExistentLobbyException : public LobbyException {
    public:
        explicit NonExistentLobbyException(const std::string &error) : LobbyException(error) {};
    };
}

#endif