/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** update_server_offline
*/

#include "protocol/greeting.h"

#include "ai_request.h"
#include "gui_update.h"

void gui_update_server_offline(zappy_t *zappy)
{
    post_header(zappy->server->gui, (payload_header_t){
        .size = sizeof(response_payload_server_disconnected_t),
        .type = SERVER_OFFLINE
    });

    post_response_server_disconnected(zappy->server->gui, (response_payload_server_disconnected_t){
        .offline = true,
    });
}
