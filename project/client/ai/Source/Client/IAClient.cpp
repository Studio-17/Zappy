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
    _inventory = {
        {"food", 10},
        {"linemate", 0},
        {"deraumere", 0},
        {"sibur", 0},
        {"mendiane", 0},
        {"phiras", 0},
        {"thystame", 0}
    };
    // _timeLimit = {
    //     {"Forward", 7},
    //     {"Right", 7},
    //     {"Left", 7},
    //     {"Look", 7},
    //     {"Inventory", 1},
    //     {"Broadcast text", 7},
    //     {"Connect_nbr", 0},
    //     {"Fork", 42},
    //     {"Eject", 7},
    //     {"Take ", 7},
    //     {"Set ", 7},
    //     {"Incantation", 300},
    // };
    _actionCommands = {
        {ACTIONS::FORWARD, "Forward\n"},
        {ACTIONS::RIGHT, "Right\n"},
        {ACTIONS::LEFT, "Left\n"},
        {ACTIONS::LOOK, "Look\n"},
        {ACTIONS::INVENTORY, "Inventory\n"},
        {ACTIONS::BROADCAST_TEXT, "Broadcast text\n"},
        {ACTIONS::CONNECT_NBR, "Connect_nbr\n"},
        {ACTIONS::FORK, "Fork\n"},
        {ACTIONS::EJECT, "Eject\n"},
        {ACTIONS::INCANTATION, "Incantation\n"},
    };
}

IAClient::~IAClient()
{
}

void IAClient::postRequest(int socketId, std::string const &request)
{
    dprintf(socketId, "%s\n", request.c_str());
}

void IAClient::postRequest(int socketId, ACTIONS request)
{
    dprintf(socketId, "%s\n", _actionCommands.at(request).c_str());
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

void IAClient::serverSentResponse()
{
    // CODE HERE ALL RESPONSES RELATED FUNCTIONS

    return;
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


void IAClient::setupOptions(int ac, char **av)
{
    _options->setupOptions(ac, av);
}

void IAClient::handleOptions()
{
    _options->handleOptions();
}

// void IAClient::handleAction(ACTIONS action)
// {
    // std::pair<ACTIONS, std::string> response;

    // response.first = action;
    // postRequest(_socket, _actionCommands.at(action));
    // response.second = getRequest(_socket);
    // return response;
// }
