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

static int count_team_members(zappy_t *zappy, char *team_name)
{
    int team_members = 0;

    for (int index = 0; index < zappy->server->clients; index += 1) {

        if (strncmp(team_name, zappy->client[index].team_name, strlen(team_name)) == 0) {

            team_members += 1;

        }

    }

    return (team_members);
}

static bool create_player(zappy_t *zappy, int socket, char *team_name)
{
    player_t player = {
        .id = zappy->server->clients,
        .level = 1,
        .position = (position_t){rand() % zappy->options->width, rand() % zappy->options->height},
        .orientation = NORTH,
        .elevation_status = NONE,
        .resource_inventory = malloc(sizeof(inventory_resource_t) * NB_ITEMS),
        .units = 1260,
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
        .list = NULL,
        .team_members = 0,
        .clock = clock(),
    };

    int team_members_connected = count_team_members(zappy, team_name);
    int client_nb = zappy->options->clients_nb - count_team_members(zappy, team_name) - 1;

    if (client_nb < 0)
        return (false);

    strcpy(zappy->client[zappy->server->clients].team_name, team_name);
    zappy->client[zappy->server->clients].team_members = team_members_connected;
    zappy->client[zappy->server->clients].client_nb = client_nb;

    zappy->server->clients += 1;

    return (true);
}

static bool get_team_name(zappy_t *zappy, int socket, bool *is_gui)
{
    char team_name[256];
    bool valid_team_name = false;
    int is_gui_team = 0;
    bool can_player_connect = false;
    bzero(&team_name, sizeof(team_name));

    if (read(socket, &team_name, sizeof(team_name)) < 0)
        perror("get_team_name read");

    for (int index = 0; zappy->options->team_names[index]; index += 1) {

        is_gui_team = strncmp(team_name, "GRAPHIC\n", strlen("GRAPHIC\n"));

        if (strncmp(zappy->options->team_names[index], team_name, strlen(zappy->options->team_names[index]) - 1) == 0
        || is_gui_team == 0) {

            if (is_gui_team == 0) {
                initialize_gui(zappy, socket);
                *is_gui = true;

            }
            else {

                can_player_connect = create_player(zappy, socket, team_name);
                if (can_player_connect == false) {
                    dprintf(socket, "ko: create player\n");
                    return (can_player_connect);
                }

            }

            valid_team_name = true;

            printf("%s", team_name);
            break;
        }
    }

    if (!valid_team_name)
        dprintf(socket, "ko\n");

    return (valid_team_name);
}

static void post_client_num(zappy_t *zappy, int socket, bool is_gui)
{
    if (is_gui) {
        dprintf(socket, "%d\n", 0);
        return;
    }

    for (int index = 0; index <= zappy->server->clients; index += 1) {
        zappy->client[index].socket;
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
