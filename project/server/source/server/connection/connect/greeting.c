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

static void post_welcome(__attribute__((unused)) zappy_t *zappy, int socket)
{
    char *message = "WELCOME";

    dprintf(socket, "%s\n", message);
}

static bool get_team_name(zappy_t *zappy, int socket)
{
    char team_name[256];
    bool valid_team_name = false;;
    bzero(&team_name, sizeof(team_name));

    if (read(socket, &team_name, sizeof(team_name)) < 0)
        perror("get_team_name read");

    for (int index = 0; zappy->options->team_names[index]; index += 1) {
        if (strncmp(zappy->options->team_names[index], team_name, strlen(zappy->options->team_names[index]) - 1) == 0
        || strncmp(team_name, "GRAPHIC\n", strlen("GRAPHIC\n")) == 0) {
            valid_team_name = true;
            printf("%s", team_name);
            break;
        }
    }

    if (!valid_team_name)
        dprintf(socket, "ko\n");

    return (valid_team_name);
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

    if (get_team_name(zappy, client_socket)) {

        post_client_num(zappy, client_socket);

        usleep(100);

        post_map_dimensions(zappy, client_socket);

    }
}
