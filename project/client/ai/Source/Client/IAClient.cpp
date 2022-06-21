/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** Client
*/

extern "C" {
    #include "netlib.h"
    #include "protocol/greeting.h"
}

#include "IAClient.hpp"

IAClient::IAClient()
{
    _options = std::make_unique<IAOptions>();
}

IAClient::~IAClient()
{
}

void IAClient::setup()
{
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == -1)
        throw ClientErrors("Socket initialization");

    bzero(&_server, sizeof(_server));

    _server.sin_family = AF_INET;
    _server.sin_addr.s_addr = inet_addr(_options->getMachine().c_str());
    _server.sin_port = htons(_options->getPort());
}

void IAClient::connection()
{
    if (connect(_socket, (struct sockaddr *)&_server, sizeof(_server)) != 0)
        throw ClientErrors("Connect failed");
    else
        handle();
}

void IAClient::handle()
{
    std::string welcomeString;
    std::string clientNumString;
    std::string coordString;

    welcomeString = getRequest(_socket);
    std::cout << welcomeString;

    postRequest(_socket, _options->getName());

    clientNumString = getRequest(_socket);

    std::size_t found = clientNumString.find("ko\n");
    if (found != std::string::npos) {
        std::cout << "ko" << std::endl;
        exit(0);
    } else
        std::cout << clientNumString;

    coordString = getRequest(_socket);
    std::cout << coordString;
    _mapSize = coordString;
}

void IAClient::serverSentResponse()
{
    // CODE HERE ALL RESPONSES RELATED FUNCTIONS

    return;
}

void IAClient::postRequest(int socketId, std::string const &request)
{
    dprintf(socketId, "%s\n", request.c_str());
}

std::string IAClient::getRequest(int socketId)
{
    std::string response;
    response.resize(100);
    int result = 0;

    if ((result = read(socketId, (void *)response.c_str(), 100)) < 0)
        perror("AIClient: getRequest");
    response.resize(result);
    return (response);
}

void IAClient::setupOptions(int ac, char **av)
{
    _options->setupOptions(ac, av);
}

void IAClient::handleOptions()
{
    _options->handleOptions();
}

std::string IAClient::getMapSize() const
{
    return _mapSize;
}

int IAClient::getSocket() const
{
    return _socket;
}

std::string IAClient::handleAction(std::string const &action)
{
    std::string string;

    postRequest(_socket, action);
    string = getRequest(_socket);
    return string;
}
