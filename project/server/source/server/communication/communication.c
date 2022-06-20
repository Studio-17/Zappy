/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** communication
*/

#include "protocol/player.h"
#include "protocol/greeting.h"

#include "server/server.h"
#include "server/communication/communication.h"
#include "server/communication/request/request.h"

static const gui_request_t gui_request_to_handle[] = {
    {
        .type = MAP_SIZE,
        .handler = &request_map_size
    },
    {
        .type = CONTENT_TILE,
        .handler = &request_tile_content
    },
    {
        .type = NAME_OF_TEAMS,
        .handler = &request_team_names
    },
    {
        .type = PLAYER_CONNECTED,
        .handler = &request_player_connected
    },
    {
        .type = PLAYER_POSITION,
        .handler = &request_player_position
    },
    {
        .type = PLAYER_LEVEL,
        .handler = &request_player_level
    },
    {
        .type = PLAYER_INVENTORY,
        .handler = &request_player_inventory
    },
    {
        .type = TIME_UNIT,
        .handler = &request_time_unit
    },
    {
        .type = TIME_UNIT_MODIFICATION,
        .handler = &request_time_unit_modification
    },
};

void request_map_size(zappy_t *zappy, void *request_data)
{
    int socket = zappy->server->sd->socket_descriptor;
    request_payload_t payload = *(request_payload_t *)request_data;

    // should i post a header here too ?
    post_response_map(socket, (response_payload_map_t) {
        .status = true,
        .width = zappy->map->width,
        .height = zappy->map->height,
    });
}

void request_tile_content(zappy_t *zappy, void *request_data)
{

}

void request_team_names(zappy_t *zappy, void *request_data)
{

}

void request_player_connected(zappy_t *zappy, void *request_data)
{

}

void request_player_position(zappy_t *zappy, void *request_data)
{

}

void request_player_inventory(zappy_t *zappy, void *request_data)
{

}

void request_player_level(zappy_t *zappy, void *request_data)
{

}

void request_time_unit(zappy_t *zappy, void *request_data)
{

}

void request_time_unit_modification(zappy_t *zappy, void *request_data)
{

}

static void *get_generic_request(int client_socket, int size_to_read)
{
    void *data = malloc(size_to_read);

    if (read(client_socket, data, size_to_read) < 0)
        perror("get_generic_request read");

    return (data);
}

void listen_clients(zappy_t *zappy)
{
    void *request_data = NULL;

    for (int index = 0; index < zappy->server->ss->max_client; index += 1) {

        zappy->server->sd->socket_descriptor = zappy->server->ss->client[index];

        // payload_header_t header = get_header(zappy->server->sd->socket_descriptor);

        // request_data = get_generic_request(zappy->server->sd->socket_descriptor, header.size);

        // gui_request_to_handle[header.type].handler(zappy, request_data);
    }
}
