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
    _timeLimit = {
        {"Forward\n", 7},
        {"Right\n", 7},
        {"Left\n", 7},
        {"Look\n", 7},
        {"Inventory\n", 1},
        {"Broadcast text\n", 7},
        {"Connect_nbr\n", 0},
        {"Fork\n", 42},
        {"Eject\n", 7},
        {"Take ", 7},
        {"Set ", 7},
        {"Incantation\n", 300},
    };
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
    setMapSize(coordString);
    createMap(_mapSize.first, _mapSize.second);
}

void IAClient::createMap(int mapHeight, int mapWidth)
{
    std::vector<std::map<std::string, int>> tmp;

    for (std::size_t line = 0; line < mapWidth; line++) {
        for (size_t col = 0; col < mapHeight; col++)
            tmp.emplace_back(createTile());
        _contentOfMap.emplace_back(tmp);
        tmp.clear();
    }
}

std::map<std::string, int> IAClient::createTile()
{
    std::map<std::string, int> tile;
    tile.emplace("food", 0);
    tile.emplace("linemate", 0);
    tile.emplace("deraumere", 0);
    tile.emplace("sibur", 0);
    tile.emplace("mendiane", 0);
    tile.emplace("phiras", 0);
    tile.emplace("thystame", 0);
    return tile;
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
