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
#include "protocol/map.h"

#include "server/server.h"
#include "server/communication/request/request.h"

static void post_welcome(__attribute__((unused)) zappy_t *zappy, int socket)
{
    char *message = "WELCOME";

    dprintf(socket, "%s\n", message);
}

static void initialize_gui(zappy_t *zappy, int socket)
{
    zappy->server->gui = socket;
    zappy->server->is_gui_connected = true;
}

static bool get_team_name(zappy_t *zappy, int socket, bool *is_gui)
{
    bool valid_team_name = false;
    char *team_name = read_in_socket(socket);

    if (!team_name)
        perror("get_team_name read");

    printf("there is %d player(s) connected\n", zappy->server->clients);
    if (strcmp(team_name, "GRAPHIC\n") == 0) {
        initialize_gui(zappy, socket);
        *is_gui = true;
        free(team_name);
        return true;
    }
    for (int index = 0; zappy->options->team_names[index]; index += 1) {
        if (strncmp(zappy->options->team_names[index], team_name, strlen(zappy->options->team_names[index])) == 0) {
            if (!create_player(zappy, socket, team_name)) {
                dprintf(socket, "ko: create player\n");
                return false;
            }
            valid_team_name = true;
            break;
        }
    }
    if (!valid_team_name)
        dprintf(socket, "ko\n");
    free(team_name);
    return (valid_team_name);
}

static void post_client_num(zappy_t *zappy, int socket, bool is_gui)
{
    if (is_gui) {
        dprintf(socket, "%d\n", 0);
        return;
    }

    for (int index = 0; index <= zappy->server->clients; index += 1) {
        if (zappy->client[index].socket == socket) {
            dprintf(socket, "%d\n", zappy->client[index].client_nb);
            return;
        }
    }
    return;
}

static void post_map_dimensions(zappy_t *zappy, int socket)
{
    dprintf(socket, "%d %d\n", zappy->options->width, zappy->options->height);
}

bool greeting_protocol(zappy_t *zappy, int client_socket)
{
    post_welcome(zappy, client_socket);
    bool is_gui = false;

    if (get_team_name(zappy, client_socket, &is_gui)) {

        post_client_num(zappy, client_socket, is_gui);

        usleep(100);

        post_map_dimensions(zappy, client_socket);
    }
    return is_gui;
}
