/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** update_map_size
*/

#include "protocol/greeting.h"

#include "ai_request.h"
#include "gui_update.h"

void gui_update_map_size(zappy_t *zappy)
{
    post_header(zappy->server->gui, (payload_header_t){
        .id = SERVER,
        .size = sizeof(response_payload_map_t),
        .type = MAP_SIZE
    });

    post_response_map(zappy->server->gui, (response_payload_map_t) {
        .status = true,
        .width = zappy->map->width,
        .height = zappy->map->height,
    });
}
