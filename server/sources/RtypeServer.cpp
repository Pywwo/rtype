/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** RtypeServer
*/

#include <network/datagram/ConnectServerDatagram.hpp>
#include "RtypeServer.hpp"

bool rtype::network::RtypeServer::caughtSigInt = false;

const std::map<rtype::network::RtypeDatagram::RtypeOpCode, rtype::network::RtypeServer::handleFunc> rtype::network::RtypeServer::_opCodeHandleMap = {
        {rtype::network::RtypeDatagram::RtypeOpCodeConnectServer, &RtypeServer::handleConnectServer}, // 120
        {rtype::network::RtypeDatagram::RtypeOpCodeCreateLobby, &RtypeServer::handleCreateLobby}, // 220
        {rtype::network::RtypeDatagram::RtypeOpCodeFetchLobbies, &RtypeServer::handleFetchLobbies}, // 221
        {rtype::network::RtypeDatagram::RtypeOpCodeInput, &RtypeServer::handleInput}, // 320
        {rtype::network::RtypeDatagram::RtypeOpCodeConnectLobby, &RtypeServer::handleConnectLobby}, // 222
        {rtype::network::RtypeDatagram::RtypeOpCodeLeaveLobby, &RtypeServer::handleLeaveLobby}, // 223
        {rtype::network::RtypeDatagram::RtypeOpCodeRequestStartGame, &RtypeServer::handleRequestStartGame}, // 321
        {rtype::network::RtypeDatagram::RtypeOpCodeBinary, &RtypeServer::handleCodeBinary}, // 100
        {rtype::network::RtypeDatagram::RtypeOpCodeLeaveGame, &RtypeServer::handleLeaveGame}, //322
};

void rtype::network::RtypeServer::SignalHandler([[maybe_unused]] int signal)
{
    caughtSigInt = true;
}

rtype::network::RtypeServer::RtypeServer()
    : _networkManager(new NetworkManager()), _isStarted(false), _timeVal(10), _manager(GameManager::getGameManagerInstance()), _clientHosts()
{
    signal(SIGINT, &SignalHandler);
}

void rtype::network::RtypeServer::run(int port)
{
    _networkManager->start(port);
    _isStarted = true;
    while (_isStarted) {
        receive();
        if (caughtSigInt)
            stop();
        if (_manager.hasPendingDatagram()) {
            sendFirstDatagramInQueue();
        }
        std::this_thread::sleep_for(std::chrono::nanoseconds(_timeVal));
    }
}

void rtype::network::RtypeServer::stop()
{
    _isStarted = false;
    _networkManager->stop();
}

void rtype::network::RtypeServer::setTimeVal(const unsigned int &newTimeVal)
{
    _timeVal = newTimeVal;
}

unsigned int rtype::network::RtypeServer::getTimeVal() const
{
    return _timeVal;
}

void rtype::network::RtypeServer::receive()
{
    Datagram ret;

    ret = _networkManager->receive();
    if (ret.getSize() == 0)
        return;
    try {
        std::cout << "RECEIVE DATAGRAM : " << reinterpret_cast<RtypeDatagram *>(&ret)->getOpCode() << std::endl;
        (*this.*(_opCodeHandleMap.at(reinterpret_cast<RtypeDatagram *>(&ret)->getOpCode())))(*reinterpret_cast<RtypeDatagram *>(&ret));
    } catch (const std::out_of_range &err) {
        sendError(ret.getHostInfos(), "Invalid rtype datagram, refer to rtype's RFC to know datagram's formatting");
        std::cerr << "Invalid datagram !" << std::endl;
    }
}

void rtype::network::RtypeServer::handleConnection()
{

}

void rtype::network::RtypeServer::handleDisconnection()
{

}

void rtype::network::RtypeServer::handleConnectServer(RtypeDatagram &data)
{
    uint64_t userId;
    HostInfos info = data.getHostInfos();

    reinterpret_cast<ConnectServerDatagram *>(&data)->extractConnectServerDatagram(userId, info.port);
    _clientHosts[userId] = info;
    Datagram response(info);
    reinterpret_cast<BinaryDatagram *>(&response)->createBinaryDatagram(true, "Successfully connected");
    _networkManager->send(response);
}

void rtype::network::RtypeServer::handleCreateLobby(RtypeDatagram &data)
{
    uint64_t userId;

    reinterpret_cast<CreateLobbyDatagram *>(&data)->extractCreateLobbyDatagram(userId);
    if (_clientHosts.find(userId) == _clientHosts.end()) {
        sendError(data.getHostInfos(), "The user id does not match any known user, please connect using \"120 - Connect Server\"");
        return;
    }
    uint64_t lobbyId = _manager.createLobby(userId);
    Lobby lobby;
    try {
        lobby = _manager.getLobby(lobbyId);
    } catch (LobbyException &e) {
        sendError(_clientHosts[userId], e.what());
        return;
    }
    std::vector<Lobby> availablesLobbies = _manager.getAvailableLobbies();
    for (auto &client : _clientHosts) {
        Datagram response(client.second);
        reinterpret_cast<AvailableLobbiesDatagram *>(&response)->createAvailableLobbiesDatagram(availablesLobbies.size(), availablesLobbies);
        _networkManager->send(response);
        if (_manager.getLobbyId(client.first) == lobbyId) {
            reinterpret_cast<LobbyInfosDatagram *>(&response)->createLobbyInfosDatagram(lobby);
            _networkManager->send(response);
        }
    }
}

void rtype::network::RtypeServer::handleFetchLobbies(RtypeDatagram &data)
{
    uint64_t userId;

    reinterpret_cast<FetchLobbiesDatagram *>(&data)->extractFetchLobbiesDatagram(userId);
    if (_clientHosts.find(userId) == _clientHosts.end()) {
        sendError(data.getHostInfos(), "The user id does not match any known user, please connect using \"120 - Connect Server\"");
        return;
    }
    std::vector<Lobby> availablesLobbies = _manager.getAvailableLobbies();
    for (auto &client : _clientHosts) {
        Datagram response(client.second);
        reinterpret_cast<rtype::network::AvailableLobbiesDatagram *>(&response)->createAvailableLobbiesDatagram(availablesLobbies.size(), availablesLobbies);
        _networkManager->send(response);
    }
}

void rtype::network::RtypeServer::handleInput(RtypeDatagram &data)
{
    uint64_t userId;
    uint64_t lobbyId;
    RtypeGameKeys key;
    RtypeKeyState state;

    reinterpret_cast<InputDatagram *>(&data)->extractInputDatagram(userId, lobbyId, key, state);
    if (_clientHosts.find(userId) == _clientHosts.end()) {
        sendError(data.getHostInfos(), "The user id does not match any known user, please connect using \"120 - Connect Server\"");
        return;
    }
    try {
        _manager.pushDatagramByLobby(lobbyId, data);
    } catch (std::out_of_range &e) {
        sendError(_clientHosts[userId], R"(The lobby does not match an active game, if you are in a lobby, please start game using "321 - Request Start Game". Otherwise create a lobby using "220 - Create Lobby" or join one using "222 - Connect Lobby")");
        return;
    }
    Datagram response(_clientHosts[userId]);
    reinterpret_cast<BinaryDatagram *>(&response)->createBinaryDatagram(true, "");
}

void rtype::network::RtypeServer::handleLeaveGame(RtypeDatagram &data)
{
    uint64_t userId;
    uint64_t lobbyId;

    reinterpret_cast<LeaveGameDatagram *>(&data)->extractLeaveGameDatagram(userId, lobbyId);
    if (_clientHosts.find(userId) == _clientHosts.end()) {
        sendError(data.getHostInfos(), "The user id does not match any known user, please connect using \"120 - Connect Server\"");
        return;
    }
    try {
        _manager.pushDatagramByLobby(lobbyId, data);
    } catch (std::out_of_range &e) {
        sendError(_clientHosts[userId], R"(The lobby does not match an active game, if you are in a lobby, please start game using "321 - Request Start Game". Otherwise create a lobby using "220 - Create Lobby" or join one using "222 - Connect Lobby")");
    }
}

void rtype::network::RtypeServer::handleCodeBinary(RtypeDatagram &data)
{
    BinaryDatagram codeBinary = *reinterpret_cast<BinaryDatagram *>(&data);
}

void rtype::network::RtypeServer::handleConnectLobby(RtypeDatagram &data)
{
    uint64_t userId;
    uint64_t lobbyId;

    reinterpret_cast<ConnectLobbyDatagram *>(&data)->extractConnectLobbyDatagram(userId, lobbyId);
    if (_clientHosts.find(userId) == _clientHosts.end()) {
        sendError(data.getHostInfos(), "The user id does not match any known user, please connect using \"120 - Connect Server\"");
        return;
    }
    Lobby lobby;
    try {
        _manager.joinLobby(userId, lobbyId);
        lobby = _manager.getLobby(lobbyId);
    } catch (LobbyException &e) {
        sendError(_clientHosts[userId], e.what());
        return;
    }
    std::vector<Lobby> availablesLobbies = _manager.getAvailableLobbies();
    for (auto &client : _clientHosts) {
        Datagram response(client.second);
        reinterpret_cast<AvailableLobbiesDatagram *>(&response)->createAvailableLobbiesDatagram(availablesLobbies.size(), availablesLobbies);
        _networkManager->send(response);
        if (_manager.getLobbyId(client.first) == lobbyId) {
            reinterpret_cast<LobbyInfosDatagram *>(&response)->createLobbyInfosDatagram(lobby);
            _networkManager->send(response);
        }
    }
}

void rtype::network::RtypeServer::handleLeaveLobby(RtypeDatagram &data)
{
    uint64_t userId;
    uint64_t lobbyId;

    reinterpret_cast<LeaveLobbyDatagram *>(&data)->extractLeaveLobbyDatagram(userId, lobbyId);
    if (_clientHosts.find(userId) == _clientHosts.end()) {
        sendError(data.getHostInfos(), "The user id does not match any known user, please connect using \"120 - Connect Server\"");
        return;
    }
    Lobby lobby;
    try {
        _manager.leaveLobby(userId, lobbyId);
    } catch (LobbyException &e) {
        sendError(_clientHosts[userId], e.what());
        return;
    }
    try {
        lobby = _manager.getLobby(lobbyId);
    } catch (NonExistentLobbyException &e) {
        std::vector<Lobby> availablesLobbies = _manager.getAvailableLobbies();
        for (auto &client : _clientHosts) {
            Datagram response(client.second);
            reinterpret_cast<AvailableLobbiesDatagram *>(&response)->createAvailableLobbiesDatagram(availablesLobbies.size(), availablesLobbies);
            _networkManager->send(response);
        }
        return;
    }
    std::vector<Lobby> availablesLobbies = _manager.getAvailableLobbies();
    for (auto &client : _clientHosts) {
        Datagram response(client.second);
        reinterpret_cast<AvailableLobbiesDatagram *>(&response)->createAvailableLobbiesDatagram(availablesLobbies.size(), availablesLobbies);
        _networkManager->send(response);
        if (_manager.getLobbyId(client.first) == lobbyId) {
            reinterpret_cast<LobbyInfosDatagram *>(&response)->createLobbyInfosDatagram(lobby);
            _networkManager->send(response);
        }
    }
}

void rtype::network::RtypeServer::handleRequestStartGame(RtypeDatagram &data)
{
    uint64_t userId;
    uint64_t lobbyId;
    Lobby lobby;
    std::map<uint64_t, HostInfos> listInfos;

    reinterpret_cast<RequestStartGameDatagram *>(&data)->extractRequestStartGameDatagram(userId, lobbyId);
    if (_clientHosts.find(userId) == _clientHosts.end()) {
        sendError(data.getHostInfos(), "The user id does not match any known user, please connect using \"120 - Connect Server\"");
        return;
    }
    try {
        lobby = _manager.getLobby(lobbyId);
    } catch (LobbyException &e) {
        sendError(_clientHosts[userId], e.what());
        return;
    }
    for (auto it : lobby.player) {
        if (it.id != 0) {
            listInfos[it.id] = _clientHosts[it.id];
        }
    }
    try {
        _manager.handleStartGame(lobbyId, listInfos);
    } catch (LobbyException &e) {
        sendError(_clientHosts[userId], e.what());
    }
    std::vector<Lobby> availablesLobbies = _manager.getAvailableLobbies();
    for (auto &client : _clientHosts) {
        Datagram response(client.second);
        reinterpret_cast<rtype::network::AvailableLobbiesDatagram *>(&response)->createAvailableLobbiesDatagram(availablesLobbies.size(), availablesLobbies);
        _networkManager->send(response);
    }
}

void rtype::network::RtypeServer::sendFirstDatagramInQueue()
{
    Datagram ret;

    ret = _manager.getFirstElementInQueue();
    _manager.popFirstElementInQueue();
    _networkManager->send(ret);
}

void rtype::network::RtypeServer::sendError(const rtype::network::HostInfos &hostInfos, const std::string &error) const
{
    Datagram response(hostInfos);
    reinterpret_cast<BinaryDatagram *>(&response)->createBinaryDatagram(false, error);
    _networkManager->send(response);
    std::cerr << error << std::endl;
}
