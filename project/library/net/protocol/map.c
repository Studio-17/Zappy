/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** map
*/

#include "protocol/map.h"


void post_response_content_map(int socket, response_payload_content_map_t response)
{
    write(socket, &response, sizeof(response_payload_content_map_t));
}

request_payload_content_map_t get_request_content_map(int socket)
{
    request_payload_content_map_t request;

    if (read(socket, &request, sizeof(request_payload_content_map_t)) < 0)
        perror("get_request_content_map read");

    return (request);
}

void post_request_content_map(int socket, request_payload_content_map_t request)
{
    write(socket, &request, sizeof(request_payload_content_map_t));
}
