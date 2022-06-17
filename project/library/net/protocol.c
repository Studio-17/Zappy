/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** protocol
*/

#include "netlib.h"

void post_header(int socket, payload_header_t header)
{
    write(socket, &header, sizeof(payload_header_t));
}

payload_header_t get_header(int socket)
{
    payload_header_t header;

    if (read(socket, &header, sizeof(payload_header_t)) < 0)
        perror("get_header read");

    return (header);
}

void post_request(int socket, request_payload_t request)
{
    write(socket, &request, sizeof(request_payload_t));
}

request_payload_t get_request(int socket)
{
    request_payload_t request;

    if (read(socket, &request, sizeof(request_payload_t)) < 0)
        perror("get_request read");

    return (request);
}

void post_response(int socket, response_payload_t response)
{
    write(socket, &response, sizeof(response_payload_t));
}

response_payload_t get_response(int socket)
{
    response_payload_t response;

    if (read(socket, &response, sizeof(response_payload_t)) < 0)
        perror("get_response read");

    return (response);
}

void post_response_client_number(int socket, response_client_number_t request)
{
    write(socket, &request, sizeof(response_client_number_t));
}

response_payload_client_number_t get_response_client_number(int socket)
{
    response_payload_client_number_t response;

    if (read(socket, &response, sizeof(response_payload_client_number_t)) < 0)
        perror("get_response_client_number read");

    return (response);
}

response_payload_map_t get_response_map(int socket)
{
    response_payload_map_t response;

    if (read(socket, &response, sizeof(response_payload_map_t)) < 0)
        perror("get_response_map read");

    return (response);
}

void post_response_map(int socket, response_payload_map_t request)
{
    write(socket, &request, sizeof(response_payload_map_t));
}

void post_response_player_position(int socket, response_payload_player_position_t response)
{
    write(socket, &response, sizeof(response_payload_player_position_t));
}

request_payload_player_position_t get_request_player_position(int socket)
{
    request_payload_player_position_t request;

    if (read(socket, &request, sizeof(request_payload_player_position_t)) < 0)
        perror("get_request_player_position read");

    return (request);
}

void post_request_player_position(int socket, request_payload_player_position_t request)
{
    write(socket, &request, sizeof(request_payload_player_position_t));
}
