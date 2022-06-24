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
    std::vector<std::map<std::string, bool>> tmp;

    for (int line = 0; line < mapWidth; line++) {
        for (int col = 0; col < mapHeight; col++)
            tmp.emplace_back(createTile());
        _contentOfMap.emplace_back(tmp);
        tmp.clear();
    }
}

std::map<std::string, bool> IAClient::createTile()
{
    std::map<std::string, bool> tile;
    tile.emplace("food", false);
    tile.emplace("linemate", false);
    tile.emplace("deraumere", false);
    tile.emplace("sibur", false);
    tile.emplace("mendiane", false);
    tile.emplace("phiras", false);
    tile.emplace("thystame", false);
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

void IAClient::fillInTheMap(std::vector<std::vector<std::string>> content, std::pair<int, int> position, std::pair<int, int> direction)
{
    std::cout << "Not filled yet" << std::endl;
}

void IAClient::serverSentResponse()
{
    // CODE HERE ALL RESPONSES RELATED FUNCTIONS

    return;
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

std::string IAClient::handleAction(std::string const &action)
{
    std::string string;

    postRequest(_socket, action);
    string = getRequest(_socket);
    return string;
}
