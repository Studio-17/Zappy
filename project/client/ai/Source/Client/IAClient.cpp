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
    _timeLimit = {
        {"Forward", 7},
        {"Right", 7},
        {"Left", 7},
        {"Look", 7},
        {"Inventory", 1},
        {"Broadcast text", 7},
        {"Connect_nbr", 0},
        {"Fork", 42},
        {"Eject", 7},
        {"Take ", 7},
        {"Set ", 7},
        {"Incantation", 300},
    };
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
        {ACTIONS::SET_FOOD, "Set "},
        {ACTIONS::SET_LINEMATE, "Set Food\n"},
        {ACTIONS::SET_DERAUMERE, "Set Linemate\n"},
        {ACTIONS::SET_SIBUR, "Set Sibur\n"},
        {ACTIONS::SET_MENDIANE, "Set Mendiane\n"},
        {ACTIONS::SET_PHIRAS, "Set Phiras\n"},
        {ACTIONS::SET_THYSTAME, "Set Thystame\n"},
        {ACTIONS::TAKE_FOOD, "Take Food\n"},
        {ACTIONS::TAKE_LINEMATE, "Take Linemate\n"},
        {ACTIONS::TAKE_DERAUMERE, "Take Deraumere\n"},
        {ACTIONS::TAKE_SIBUR, "Take Sibur\n"},
        {ACTIONS::TAKE_MENDIANE, "Take Mendiane\n"},
        {ACTIONS::TAKE_PHIRAS, "Take Phiras\n"},
        {ACTIONS::TAKE_THYSTAME, "Take Thystame\n"},
    };
}

IAClient::~IAClient()
{
}

void IAClient::setMapSize(std::string str)
{
    std::string delimiter = " ";
    size_t pos = str.find(delimiter);
    std::string token = str.substr(0, pos);

    _mapSize.first = std::stoi(token);
    str.erase(0, pos + delimiter.length());
    _mapSize.second = std::stoi(str);
}

void IAClient::postRequest(int socketId, std::string const &request)
{
    dprintf(socketId, "%s\n", request.c_str());
}

void IAClient::postRequest(int socketId, ACTIONS request)
{
    dprintf(socketId, "%s", _actionCommands.at(request).c_str());
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
    setMapSize(coordString);
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
