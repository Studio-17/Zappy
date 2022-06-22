/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** client
*/

#define _GNU_SOURCE

#include "minilib.h"
#include "netlib.h"
#include "protocol/greeting.h"
#include "protocol/player.h"

#include <fcntl.h>

#include "server/server.h"
#include "server/communication/request/request.h"

static void send_new_player_connected_to_gui(zappy_t *zappy, int player_index)
{
    post_header(zappy->server->gui, (payload_header_t){
        .id = SERVER,
        .size = sizeof(response_payload_player_connected_t),
        .type = PLAYER_CONNECTED}
    );

    post_response_player_connected(zappy->server->gui, (response_payload_player_connected_t){
        .id = player_index,
        .level = zappy->client[player_index].player.level,
        .orientation = zappy->client[player_index].player.orientation,
        .position = zappy->client[player_index].player.position,
    });
}

static void send_content_map_tile(zappy_t *zappy, int player_index)
{
    post_header(zappy->server->gui, (payload_header_t){
        .id = SERVER,
        .size = sizeof(response_payload_content_tile_t),
        .type = CONTENT_TILE,
    });

    int x = 4;
    int y = 4;

    post_response_content_tile(zappy->server->gui, (response_payload_content_tile_t){
        .position.x = x,
        .position.y = y,
        .food = 0,
        .linemate = 0,
        .deraumere = 0,
        .sibur = 0,
        .mendiane = 0,
        .phiras = 0,
        .thystame = 1,
    });
}

static void create_player(zappy_t *zappy, int socket)
{
    player_t player = (player_t){
        .id = zappy->server->clients,
        .level = 1,
        .position = (position_t){rand() % zappy->options->width, rand() % zappy->options->height},
        .orientation = NORTH,
        // .resource_inventory = NULL,
    };

    // for (int index = 0; index < NB_ITEMS; index += 1) {
    //     player.resource_inventory[index].resource = (enum ITEM)index;
    //     player.resource_inventory[index].quantity = 1;
    // }

    zappy->client[zappy->server->clients] = (ai_client_t){socket, zappy->server->clients, AI, player};
}

void connect_client(zappy_t *zappy)
{
    int client_socket;
    int saved_index = 0;

    if (FD_ISSET(zappy->server->server_socket->server, &zappy->server->socket_descriptor->readfd))
    {
        if ((client_socket = accept(zappy->server->server_socket->server,
                                 (struct sockaddr *)&zappy->server->address, (socklen_t *)&zappy->server->address_length)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        if (!greeting_protocol(zappy, client_socket)) {
            for (int index = 0; index < zappy->server->server_socket->max_client; index += 1) {
                if (zappy->client[index].socket == 0) {
                    saved_index = index;
                    zappy->client[index].socket = client_socket;
                    zappy->server->server_socket->client[index] = client_socket;
                    break;
                }
            }

            create_player(zappy, client_socket);

            zappy->server->clients += 1;
            if (zappy->server->is_gui_connected)
                send_new_player_connected_to_gui(zappy, saved_index);
        } else {
            // response_payload_content_tile_t **map_tiles = malloc(sizeof(response_payload_content_tile_t) * zappy->options->height);
            // for (int map_height = 0; map_height < zappy->options->height; map_height += 1) {

            //     map_tiles[map_height] = malloc(sizeof(response_payload_content_tile_t) * zappy->options->width);

            //     for (int map_width = 0; map_width < zappy->options->width; map_width += 1) {

            //         map_tiles[map_height][map_width].position.x = map_width;
            //         map_tiles[map_height][map_width].position.y = map_height;
            //         map_tiles[map_height][map_width].food = zappy->map->tiles[map_height][map_width].resources[FOOD].quantity;
            //         map_tiles[map_height][map_width].linemate = zappy->map->tiles[map_height][map_width].resources[LINEMATE].quantity;
            //         map_tiles[map_height][map_width].deraumere = zappy->map->tiles[map_height][map_width].resources[DERAUMERE].quantity;
            //         map_tiles[map_height][map_width].sibur = zappy->map->tiles[map_height][map_width].resources[SIBUR].quantity;
            //         map_tiles[map_height][map_width].mendiane = zappy->map->tiles[map_height][map_width].resources[MENDIANE].quantity;
            //         map_tiles[map_height][map_width].phiras = zappy->map->tiles[map_height][map_width].resources[PHIRAS].quantity;
            //         map_tiles[map_height][map_width].thystame = zappy->map->tiles[map_height][map_width].resources[THYSTAME].quantity;

            //     }
            // }
            // post_header(zappy->server->gui, (payload_header_t){
            //     .id = SERVER,
            //     .size = sizeof(request_payload_content_map_t),
            //     .type = CONTENT_MAP
            // });
            // // sleep(5);

            // post_response_content_map(zappy->server->gui, (response_payload_content_map_t){
            //     .content = map_tiles,
            // });
            usleep(300);
            send_content_map_tile(zappy, saved_index);
        }

    }


    listen_clients(zappy);
}

void clear_socket_set(server_t *server)
{
    FD_ZERO(&server->socket_descriptor->readfd);
}

void add_server_socket_to_set(server_t *server)
{
    FD_SET(server->server_socket->server, &server->socket_descriptor->readfd);
    server->socket_descriptor->max_socket_descriptor = server->server_socket->server;
}

void add_client_socket_to_set(server_t *server)
{
    for (int index = 0; index < server->server_socket->max_client; index += 1)
    {
        server->socket_descriptor->socket_descriptor = server->server_socket->client[index];

        if (server->socket_descriptor->socket_descriptor > 0)
            FD_SET(server->socket_descriptor->socket_descriptor, &server->socket_descriptor->readfd);

        if (server->socket_descriptor->socket_descriptor > server->socket_descriptor->max_socket_descriptor)
            server->socket_descriptor->max_socket_descriptor = server->socket_descriptor->socket_descriptor;
    }
}

void wait_for_connections(server_t *server)
{
    if ((select(server->socket_descriptor->max_socket_descriptor + 1, &server->socket_descriptor->readfd, NULL, NULL, NULL) < 0))
    {
        perror("select");
    }
}

void add_client_to_server(server_t *server, int client_socket)
{
    for (int index = 0; index < server->server_socket->max_client; index += 1)
    {
        if (server->server_socket->client[index] == 0)
        {
            server->server_socket->client[index] = client_socket;
            break;
        }
    }
}
