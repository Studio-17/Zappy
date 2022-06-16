/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** Client
*/

extern "C" {
    #include "netlib.h"
}

#include "Client.hpp"

Client::Client(Options const &options)
{
    _options = std::make_unique<Options>(options);
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
    char *identification = NULL;
    asprintf(&identification, "IA Client Connected on socket %d, at address %s\n", _socket, inet_ntoa(_server.sin_addr));

    // send_request(_socket, identification);
    // response_payload_t rsp = get_response_payload(get_response(_socket));

    request_payload_t request;
    request.id = _socket;
    strcpy(request.command, identification);
    send_struct_request(_socket, request);
    response_payload_t response = get_struct_response(_socket);
    printf("%d\n", response.id);
    printf("%d\n", response.status);
    printf("%s\n", response.message);

    // printf("%s\n", get_response(_socket));

    // replace with actual team name
    // send_request(_socket, "martin");
    // printf("%s\n", get_response(_socket));
}
