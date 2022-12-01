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

#include "Client.hpp"

Client::Client()
{
    _options = std::make_unique<Options>();
}

Client::~Client()
{
}

void Client::setup()
{
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == -1)
        throw ClientErrors("Socket initialization");

    bzero(&_server, sizeof(_server));

    _server.sin_family = AF_INET;
    _server.sin_addr.s_addr = inet_addr(_options->getMachine().c_str());
    _server.sin_port = htons(_options->getPort());
    std::cout << "client started function setup" << std::endl;
}

bool Client::checkConnection()
{
    if (connect(_socket, (struct sockaddr *)&_server, sizeof(_server)) != 0)
        _isConnected = false;

    else
        _isConnected = true;
    return (_isConnected);
}

void Client::connection()
{
    if (connect(_socket, (struct sockaddr *)&_server, sizeof(_server)) != 0)
        throw ClientErrors("Connect failed");
    else
        handle();
}

void Client::handle()
{
    int unblock = 0;

    std::string welcomeString;
    std::string clientNumString;
    std::string coordString;
    std::string graphic = "GRAPHIC";

    welcomeString = getRequest(_socket);
    std::cout << welcomeString;

    postRequest(_socket, graphic);

    clientNumString = getRequest(_socket);
    std::cout << clientNumString;


    coordString = getRequest(_socket);
    std::cout << coordString;
    _mapDimension = coordString;

    // UNBLOCK SOCKET
    unblock = fcntl(_socket, F_GETFL, 0);
    fcntl(_socket, F_SETFL, unblock | O_NONBLOCK);
}

void Client::postRequest(int socketId, std::string const &request)
{
    dprintf(socketId, "%s\n", request.c_str());
}

std::string Client::getRequest(int socketId)
{
    // std::cout << "getRequest";
    std::string response;
    response.resize(1024);
    int result = 0;

    if ((result = read(socketId, (void *)response.c_str(), 1024)) < 0)
        perror("AIClient: getRequest");
    response.resize(result);
    return (response);
}

std::pair<int, int> Client::getMapDimension()
{
    std::string x;
    std::string y;

    x = _mapDimension.substr(0, _mapDimension.find_first_of(" "));
    y = _mapDimension.substr(_mapDimension.find_first_of(" ") + 1, _mapDimension.length());
    auto tmp = std::make_pair<int>(std::atoi(x.c_str()), std::atoi(y.c_str()));
    return (tmp);
}

void Client::serverSentResponse()
{
    // CODE HERE ALL RESPONSES RELATED FUNCTIONS

    return;
}


void Client::setupOptions(int ac, char **av)
{
    _options->setupOptions(ac, av);
}

void Client::handleOptions()
{
    _options->handleOptions();
}

void Client::listen()
{
    char *data = nullptr;
    int readResult = 0;
    payload_header_t header = {0, 0};

    readResult = read(_socket, &header, sizeof(payload_header_t));
    if (readResult <= 0) {
        return;
    }
    data = (char*)malloc(header.size);
    readResult = read(_socket, data, header.size);
    if (readResult <= 0)
        return;
    _eventsHandler.eventReceive(data, header.type);
    free(data);
}

void Client::setMachine(std::string &machine)
{
    _options->setMachine(machine);
}

void Client::setPort(int port)
{
    _options->setPort(port);
}


