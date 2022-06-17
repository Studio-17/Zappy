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
    // SEND CLIENT TYPE & GET WELCOME MESSAGE
    post_request(_socket, request_payload_t{"IA\n"});
    response_payload_t response = get_response(_socket);
    std::cout << response.payload;

    // SEND TEAM NAME & GET OK RESPONSE
    request_payload_t request;
    strcpy(request.payload, _options->getName().c_str());
    post_request(_socket, request);
    response_payload_t team_response = get_response(_socket);
    std::cout << team_response.payload;

    // SEND INFO REQUEST & GET CLIENT NUMBER
    post_request(_socket, request_payload_t{"INFO CLIENT\n"});
    response_payload_client_number_t client_number_response = get_response_client_number(_socket);
    std::cout << client_number_response.client_id << std::endl;

    // SEND INFO REQUEST & GET MAP DIMENSIONS
    post_request(_socket, request_payload_t{"INFO MAP\n"});
    response_payload_map_t map_response = get_response_map(_socket);
    std::cout << map_response.height << " " << map_response.width << std::endl;
}

void Client::serverSentResponse()
{
    // CODE HERE ALL RESPONSES RELATED FUNCTIONS

    return;
}
