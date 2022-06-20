/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** greeting
*/

#define _GNU_SOURCE

#include "netlib.h"
#include "protocol/greeting.h"
#include "protocol/player.h"

#include "server/server.h"
#include "server/communication/request/request.h"

static void ai_protocol(zappy_t *zappy, int client_socket)
{
    request_payload_t info_client_request = get_request(client_socket);
    post_response_client_number(client_socket, (response_client_number_t) {true, zappy->server->clients});

    player_t player = (player_t) {.id = zappy->server->clients, .level = 1, .orientation = SOUTH, .position = (position_t){rand() % zappy->options->width, rand() % zappy->options->height}};
    zappy->client[zappy->server->clients] = (ai_client_t){client_socket, zappy->server->clients, AI, player};

    get_map_informations(zappy, client_socket);
}

static void gui_protocol(zappy_t *zappy, int client_socket)
{
    request_payload_t info_client_request = get_request(client_socket);
    post_response_client_number(client_socket, (response_client_number_t) {true, zappy->server->clients});

    zappy->server->gui = client_socket;
    zappy->server->is_gui_connected = true;

    get_map_informations(zappy, client_socket);
}

static void post_welcome(zappy_t *zappy, int socket)
{
    char *message = "WELCOME";

    dprintf(socket, "%s\n", message);
}

static void get_team_name(zappy_t *zappy, int socket)
{
    char team_name[256];

    if (read(socket, &team_name, sizeof(team_name)) < 0)
        perror("get_team_name read");

    if (strcmp(team_name, "GRAPHIC\n") != 0) {
        player_t player = (player_t) {.id = zappy->server->clients, .level = 1, .orientation = SOUTH, .position = (position_t){rand() % zappy->options->width, rand() % zappy->options->height}};
        zappy->client[zappy->server->clients] = (ai_client_t){socket, zappy->server->clients, AI, player};
        zappy->server->clients += 1;
    }

    printf("%s", team_name);
}

static void post_client_num(zappy_t *zappy, int socket)
{
    dprintf(socket, "%d\n", zappy->server->sd->socket_descriptor);
}

static void post_map_dimensions(zappy_t *zappy, int socket)
{
    dprintf(socket, "%d %d\n", zappy->options->width, zappy->options->height);
}

void greeting_protocol(zappy_t *zappy, int client_socket)
{
    post_welcome(zappy, client_socket);

    get_team_name(zappy, client_socket);

    post_client_num(zappy, client_socket);

    post_map_dimensions(zappy, client_socket);
}
