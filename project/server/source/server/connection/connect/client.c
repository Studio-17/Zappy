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

#include "gui_update.h"

#include "server/server.h"
#include "server/communication/request/request.h"

static void create_player(zappy_t *zappy, int socket)
{
    player_t player = (player_t){
        .id = zappy->server->clients,
        .level = 1,
        .position = (position_t){rand() % zappy->options->width, rand() % zappy->options->height},
        .orientation = NORTH,
        .elevation_status = NONE,
        .resource_inventory = malloc(sizeof(inventory_resource_t) * NB_ITEMS),
    };

    player.resource_inventory[FOOD].resource = FOOD;
    player.resource_inventory[FOOD].quantity = 10;
    for (int index = 1; index < NB_ITEMS; index += 1) {
        player.resource_inventory[index].resource = (enum ITEM)index;
        player.resource_inventory[index].quantity = 0;
    }

    zappy->client[zappy->server->clients] = (ai_client_t){
        .socket = socket,
        .client_nb = zappy->server->clients,
        .type = AI,
        .player = player,
        .list = NULL
    };
}

bool connect_client(zappy_t *zappy)
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
                if (zappy->server->server_socket->client[index] == 0) {
                    saved_index = index;
                    // zappy->client[index].socket = client_socket;
                    zappy->server->server_socket->client[index] = client_socket;
                    break;
                }
            }

            create_player(zappy, client_socket);

            zappy->server->clients += 1;
            if (zappy->server->is_gui_connected)
                update_player_connected(zappy, saved_index);
        } else {
            int cpt = 0;
            printf("%d, %d\n", zappy->options->height, zappy->options->width);
            response_payload_content_tile_t *map_tiles = malloc(sizeof(response_payload_content_tile_t) * zappy->options->height * zappy->options->width);
            for (int map_height = 0; map_height < zappy->options->height; map_height += 1) {
                for (int map_width = 0; map_width < zappy->options->width; map_width += 1) {
                    map_tiles[cpt].position.x = map_width;
                    map_tiles[cpt].position.y = map_height;
                    map_tiles[cpt].food = zappy->map->tiles[map_height][map_width].resources[FOOD].quantity;
                    map_tiles[cpt].linemate = zappy->map->tiles[map_height][map_width].resources[LINEMATE].quantity;
                    map_tiles[cpt].deraumere = zappy->map->tiles[map_height][map_width].resources[DERAUMERE].quantity;
                    map_tiles[cpt].sibur = zappy->map->tiles[map_height][map_width].resources[SIBUR].quantity;
                    map_tiles[cpt].mendiane = zappy->map->tiles[map_height][map_width].resources[MENDIANE].quantity;
                    map_tiles[cpt].phiras = zappy->map->tiles[map_height][map_width].resources[PHIRAS].quantity;
                    map_tiles[cpt].thystame = zappy->map->tiles[map_height][map_width].resources[THYSTAME].quantity;
                    cpt++;
                }
            }
            usleep(3000);
            post_header(zappy->server->gui, (payload_header_t){
                .id = SERVER,
                .size = sizeof(response_payload_content_tile_t) * zappy->options->height * zappy->options->width,
                .type = CONTENT_MAP
            });
            post_response_content_map(zappy->server->gui, map_tiles, sizeof(response_payload_content_tile_t) * zappy->options->height * zappy->options->width);
        }

    }
    return (listen_clients(zappy));
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
