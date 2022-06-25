/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** client
*/

#include "server.h"
#include "request.h"

bool setup_client(zappy_t *zappy, int max_clients)
{
    zappy->client = malloc(sizeof(ai_client_t) * max_clients);
    if (!zappy->client)
        return false;
    for (int index = 0; index != max_clients; index++) {
        zappy->client[index].player.resource_inventory = NULL;
        zappy->client[index].list = NULL;
        zappy->client[index].socket = 0;
        zappy->client[index].client_nb = 0;
        zappy->client[index].buffer = NULL;
        zappy->client[index].team_name = NULL;
    }
    return true;
}

static int count_team_members(zappy_t *zappy, char const *team_name)
{
    int team_members = 0;

    for (int index = 0; index < zappy->server->clients; index += 1)
        if (strncmp(team_name, zappy->client[index].team_name, strlen(team_name)) == 0)
            team_members += 1;
    return (team_members);
}

int create_player(zappy_t *zappy, int socket, char *team_name)
{
    int id = zappy->options->max_clients - zappy->server->clients;
    int client_nb = zappy->options->clients_nb - count_team_members(zappy, team_name) - 1;

    if (id < 0)
        return FAILURE;
    if (client_nb < 0)
        return SPECIAL_STATUS;

    player_t player = {
        .id = zappy->server->clients,
        .level = 1,
        .position = (position_t){rand() % zappy->options->width, rand() % zappy->options->height},
        .orientation = NORTH,
        .elevation_status = NONE,
        .resource_inventory = malloc(sizeof(inventory_resource_t) * NB_ITEMS),
        .units = 1260,
    };

    if (!player.resource_inventory)
        return false;
    player.resource_inventory[FOOD].resource = FOOD;
    player.resource_inventory[FOOD].quantity = 10;
    for (int index = 1; index < NB_ITEMS; index += 1) {
        player.resource_inventory[index].resource = (enum ITEM)index;
        player.resource_inventory[index].quantity = 0;
    }

    zappy->client[zappy->server->clients].id = id;
    printf("id is %d\n", id);
    zappy->client[zappy->server->clients].team_name = strdup(team_name);
    if (!zappy->client[zappy->server->clients].team_name)
        return false;
    zappy->client[zappy->server->clients].team_members = count_team_members(zappy, team_name);
    zappy->client[zappy->server->clients].client_nb = client_nb;
    zappy->client[zappy->server->clients].clock = clock();
    zappy->client[zappy->server->clients].socket = socket;
    zappy->client[zappy->server->clients].player = player;
    printf("there is now %d player(s) connected\n", zappy->server->clients);
    if (zappy->server->is_gui_connected)
        gui_update_player_connected(zappy, zappy->server->clients);
    zappy->server->clients += 1;

    return (SUCCESS);
}


/*static bool create_player(zappy_t *zappy, int socket, char *team_name)
{
    player_t player = {
        .id = zappy->server->clients,
        .level = 1,
        .position = (position_t){rand() % zappy->options->width, rand() % zappy->options->height},
        .orientation = NORTH,
        .elevation_status = NONE,
        .resource_inventory = malloc(sizeof(inventory_resource_t) * NB_ITEMS),
        .units = 0,
    };

    player.resource_inventory[FOOD].resource = FOOD;
    player.resource_inventory[FOOD].quantity = 10;
    for (int index = 1; index < NB_ITEMS; index += 1) {
        player.resource_inventory[index].resource = (enum ITEM)index;
        player.resource_inventory[index].quantity = 0;
    }

    zappy->client[zappy->server->clients] = (ai_client_t){
        .socket = socket,
        .id = 0,
        .client_nb = zappy->server->clients,
        .type = AI,
        .player = player,
        .list = NULL,
        .team_members = 0,
        .clock = clock(),
    };

    int id = zappy->options->max_clients - zappy->server->clients;

    int team_members_connected = count_team_members(zappy, team_name);
    int client_nb = zappy->options->clients_nb - count_team_members(zappy, team_name) - 1;

    if (client_nb < 0 || id < 0)
        return (false);

    zappy->client[zappy->server->clients].id = id;

    strcpy(zappy->client[zappy->server->clients].team_name, team_name);
    zappy->client[zappy->server->clients].team_members = team_members_connected;
    zappy->client[zappy->server->clients].client_nb = client_nb;

    printf("client-id(server-side): %d\n", zappy->client[zappy->server->clients].id);

    if (zappy->server->is_gui_connected)
        gui_update_player_connected(zappy, zappy->server->clients);

    zappy->server->clients += 1;

    return (true);
}*/

void free_clients(ai_client_t *clients, int max_clients)
{
    for (int index = 0; index != max_clients; index++) {
        free(clients[index].player.resource_inventory);
        free(clients[index].buffer);
        free(clients[index].team_name);
        list_t tmp_ptr = clients[index].list;
        while (tmp_ptr) {
            free((*(data_t *)tmp_ptr->value).request.data);
            tmp_ptr = tmp_ptr->next;
        }
        queue_clear(&clients[index].list);
    }
    free(clients);
}