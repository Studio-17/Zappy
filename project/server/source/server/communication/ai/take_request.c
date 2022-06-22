/*
** EPITECH PROJECT, 2022
** project
** File description:
** take_request
*/

#include "ai_request.h"

void ai_take_request(zappy_t *zappy, void *data, int player_index)
{
    char *request = (char *)data;
    char *resource = get_resource_from_request(request);

    if (resource == NULL)
        ai_response_ok_ko(zappy->server->socket_descriptor->socket_descriptor, false);
    else {
        // code here handler
        ai_response_ok_ko(zappy->server->socket_descriptor->socket_descriptor, true);
    }
}