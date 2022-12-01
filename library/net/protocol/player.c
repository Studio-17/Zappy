/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** player
*/

#include "protocol/player.h"

request_payload_player_connected_t get_request_player_connected(int socket)
{
    request_payload_player_connected_t request;

    if (read(socket, &request, sizeof(request_payload_player_connected_t)) < 0)
        perror("get_request_player_connected read");

    return (request);
}

void post_request_player_connected(int socket, request_payload_player_connected_t request)
{
    write(socket, &request, sizeof(request_payload_player_connected_t));
}

response_payload_player_connected_t get_response_player_connected(int socket)
{
    response_payload_player_connected_t response;

    if (read(socket, &response, sizeof(response_payload_player_connected_t)) < 0)
        perror("get_response_player_connected read");

    return (response);
}

void post_response_player_connected(int socket, response_payload_player_connected_t response)
{
    write(socket, &response, sizeof(response_payload_player_connected_t));
}

void post_response_data(int socket, void *response)
{
    write(socket, response, sizeof(response));
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

void post_response_player_level(int socket, response_payload_player_level_t response)
{
    write(socket, &response, sizeof(response_payload_player_level_t));
}

request_payload_player_level_t get_request_player_level(int socket)
{
    request_payload_player_level_t request;

    if (read(socket, &request, sizeof(request_payload_player_level_t)) < 0)
        perror("get_request_player_level read");

    return (request);
}

void post_request_player_level(int socket, request_payload_player_level_t request)
{
    write(socket, &request, sizeof(request_payload_player_level_t));
}

void post_response_player_inventory(int socket, response_payload_player_inventory_t response)
{
    write(socket, &response, sizeof(response_payload_player_inventory_t));
}

request_payload_player_inventory_t get_request_player_inventory(int socket)
{
    request_payload_player_inventory_t request;

    if (read(socket, &request, sizeof(request_payload_player_inventory_t)) < 0)
        perror("get_request_player_inventory read");

    return (request);
}

void post_request_player_inventory(int socket, request_payload_player_inventory_t request)
{
    write(socket, &request, sizeof(request_payload_player_inventory_t));
}

void post_response_player_orientation(int socket, response_payload_player_orientation_t response)
{
    write(socket, &response, sizeof(response_payload_player_orientation_t));
}

void post_response_player_dead(int socket, response_payload_player_dead_t response)
{
    write(socket, &response, sizeof(response_payload_player_dead_t));
}

void post_response_player_start_incantation(int socket, response_payload_player_start_incantation_t response)
{
    write(socket, &response, sizeof(response_payload_player_start_incantation_t));
}

void post_response_player_end_incantation(int socket, response_payload_player_end_incantation_t response)
{
    write(socket, &response, sizeof(response_payload_player_end_incantation_t));
}
