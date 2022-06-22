/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** ai
*/

#include "protocol/player.h"
#include "protocol/greeting.h"

#include "server/server.h"
#include "server/communication/communication.h"
#include "server/communication/request/request.h"

static const position_t direction[] = {
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}
};

void ai_base_request(zappy_t *zappy, void *data, int player_index)
{
    int socket = zappy->server->socket_descriptor->socket_descriptor;

    write(socket, "UNUSED REQUEST\n", strlen("UNUSED REQUEST\n"));
}

void ai_response_ok_ko(int socket, bool status)
{
    size_t message_size = 4;

    write(socket, (status ? "ok\n" : "ko\n" ), message_size);
}

void ai_response_string(int socket, char *message)
{
    dprintf(socket, "%s\n", message);
}

static void move(zappy_t *zappy, position_t movement, int player_index)
{
    zappy->client[player_index].player.position.x += movement.x;
    if (zappy->client[player_index].player.position.x < 0)
        zappy->client[player_index].player.position.x = zappy->map->width - 1;
    else if (zappy->client[player_index].player.position.x > zappy->map->width - 1)
        zappy->client[player_index].player.position.x = 0;

    zappy->client[player_index].player.position.y += movement.y;
    if (zappy->client[player_index].player.position.y < 0)
        zappy->client[player_index].player.position.y = zappy->map->height - 1;
    else if (zappy->client[player_index].player.position.y > zappy->map->height - 1)
        zappy->client[player_index].player.position.y = 0;
}

static void post_player_movement(zappy_t *zappy, int player_index)
{
    post_header(zappy->server->gui, (payload_header_t){
        .id = SERVER,
        .size = sizeof(response_payload_player_position_t),
        .type = PLAYER_POSITION
    });

    post_response_player_position(zappy->server->gui, (response_payload_player_position_t){
        .status = true,
        .player_id = player_index,
        .position = zappy->client[player_index].player.position,
    });
}

void ai_forward_request(zappy_t *zappy, void *data, int player_index)
{
    position_t movement = direction[zappy->client[player_index].player.orientation];

    move(zappy, movement, player_index);

    post_player_movement(zappy, player_index);

    ai_response_ok_ko(zappy->server->socket_descriptor->socket_descriptor, true);
}

void ai_right_request(zappy_t *zappy, void *data, int player_index)
{
    int socket = zappy->server->socket_descriptor->socket_descriptor;

    zappy->client[player_index].player.orientation += 1;
    if (zappy->client[player_index].player.orientation > WEST)
        zappy->client[player_index].player.orientation = NORTH;
    ai_response_ok_ko(socket, true);
}

void ai_left_request(zappy_t *zappy, void *data, int player_index)
{
    int socket = zappy->server->socket_descriptor->socket_descriptor;

    if (zappy->client[player_index].player.orientation < NORTH)
        zappy->client[player_index].player.orientation = WEST;
    else
        zappy->client[player_index].player.orientation -= 1;
    ai_response_ok_ko(socket, true);
}

void print_tile_content(int socket, tile_t const tile, bool first)
{
    bool first_resource = true;

    for (int index = 0; index < NB_ITEMS; index++)
        if (tile.resources[index].quantity) {
            if (!first && first_resource) {
                dprintf(socket, " ");
                first_resource = false;
            } else if (!first_resource)
                dprintf(socket, " ");
            dprintf(socket, "%s", tile.resources[index].name);
        }
}

void ai_look_request(zappy_t *zappy, void *data, int player_index)
{
    int socket = zappy->server->socket_descriptor->socket_descriptor;
    position_t player_orientation = direction[zappy->client[player_index].player.orientation];
    position_t position = zappy->client[player_index].player.position;
    int nb_tiles = 0;

    for (int i = 0; i <= zappy->client[player_index].player.level; i++)
        nb_tiles += 1 + (i * 2);
    tile_t *tiles = malloc(sizeof(tile_t) * nb_tiles);
    if (!tiles)
        return;
    int tiles_index = 0;
    bool first = true;
    dprintf(socket, "[");
    for (int i = 0; i <= zappy->client[player_index].player.level; i++) {
        for (int index = -i; index <= i; index++) {
            if (!first)
                dprintf(socket, ",");
            position_t tmp_pos;
            tmp_pos.x = zappy->client[player_index].player.position.x + (player_orientation.x * index);
            if (tmp_pos.x >= zappy->map->width)
                tmp_pos.x = 0;
            else if (tmp_pos.x < 0)
                tmp_pos.x = zappy->map->width - 1;
                        // tiles[tiles_index].x = zappy->client[player_index].player.position.x + (player_orientation.x * index);
            tmp_pos.y = zappy->client[player_index].player.position.y + (player_orientation.y * index);
            if (tmp_pos.y >= zappy->map->height)
                tmp_pos.y = 0;
            else if (tmp_pos.y < 0)
                tmp_pos.y = zappy->map->height - 1;

                        // tiles[tiles_index].y = zappy->client[player_index].player.position.y + (player_orientation.y * index);
            print_tile_content(socket, zappy->map->tiles[tmp_pos.y][tmp_pos.x], first);
            tiles[tiles_index] = zappy->map->tiles[tmp_pos.y][tmp_pos.x];
            tiles_index++;
            if (first)
                first = false;
        }
    }
    dprintf(socket, "]\n");
}

static int get_resource_from_request(char *target)
{
    char **request_content = my_strtok(target, ' ');
    int length = strlen(request_content[1]);
    char *resource_set[] = {
        "Food",
        "Linemate",
        "Deraumere",
        "Sibur",
        "Mendiane",
        "Phiras",
        "Thystame",
        NULL
    };


    for (int index = 0; resource_set[index]; index += 1) {

        if (strncmp(request_content[1], resource_set[index], length - 2) == 0) {
            return (index);
        }

    }
    return (-1);
}

void ai_take_request(zappy_t *zappy, void *data, int player_index)
{
    char *request = (char *)data;
    enum ITEM resource = (enum ITEM)get_resource_from_request(request);

    if (resource == -1)
        ai_response_ok_ko(zappy->server->socket_descriptor->socket_descriptor, false);
    else {

        zappy->client[player_index].player.resource_inventory[resource].quantity += 1;

        int x = zappy->client[player_index].player.position.x;
        int y = zappy->client[player_index].player.position.y;

        zappy->map->tiles[x][y].resources[resource].quantity -= 1;

        // UPDATE MAP TILE IN GUI

        ai_response_ok_ko(zappy->server->socket_descriptor->socket_descriptor, true);
    }
}

void ai_set_request(zappy_t *zappy, void *data, int player_index)
{
    char *request = (char *)data;
    enum ITEM resource = (enum ITEM)get_resource_from_request(request);

    if (resource == -1)
        ai_response_ok_ko(zappy->server->socket_descriptor->socket_descriptor, false);
    else {

        if (zappy->client[player_index].player.resource_inventory[resource].quantity > 0) {
            zappy->client[player_index].player.resource_inventory[resource].quantity -= 1;

            int x = zappy->client[player_index].player.position.x;
            int y = zappy->client[player_index].player.position.y;

            zappy->map->tiles[x][y].resources[resource].quantity += 1;

            // UPDATE MAP TILE IN GUI

            ai_response_ok_ko(zappy->server->socket_descriptor->socket_descriptor, true);
        } else
            ai_response_ok_ko(zappy->server->socket_descriptor->socket_descriptor, false);
    }
}

/*
elevation   nb of players   linemate    deraumere   sibur   mendiane    phiras  thystame
1->2        1               1           0           0       0           0       0
2->3        2               1           1           1       0           0       0
3->4        2               2           0           1       0           2       0
4->5        4               1           1           2       0           1       0
5->6        4               1           2           1       3           0       0
6->7        6               1           2           3       0           1       0
7->8        6               2           2           2       2           2       1
*/

static bool check_elevation(zappy_t *zappy, int elevation_index, int player_level, int player_index)
{
    // PRELIMINARIES
    position_t player_position = zappy->client[player_index].player.position;

    // PRE FOR TILE CHECKS
    int player_needed = zappy->elevation[elevation_index].elevation_step->player_needed;
    // CHECK PLAYERS ON TILE
    int players_on_tile = 0;
    for (int index = 0; index != zappy->server->clients; index += 1) {
        if (zappy->client[index].player.position.x == player_position.x
        && zappy->client[index].player.position.y == player_position.y) {
            players_on_tile += 1;
        }
    }
    if (players_on_tile != zappy->elevation[elevation_index].elevation_step->player_needed)
        return (false);

    // PRE FOR RESOURCE CHECKS
    elevation_resources_t *resources_need = zappy->elevation[elevation_index].elevation_step->resource;
    resources_t *tile_resources = zappy->map->tiles[player_position.x][player_position.y].resources;

    // CHECK RESOURCES ON TILE
    for (int index = 1; index != NB_ITEMS; index += 1) {
        if (resources_need[index].quantity_needed != tile_resources[index].quantity) {

            return (false);
        }
    }

    zappy->client[player_index].player.level += 1;
    return (true);
}

static void ai_incantation_request(zappy_t *zappy, void *data, int player_index)
{
    int elevation_processus_index = zappy->client[player_index].player.level - 1;

    printf("current player level: %d\n", zappy->client[player_index].player.level);
    printf("elevation processus index: %d\n", elevation_processus_index);


    if (check_elevation(zappy, elevation_processus_index, zappy->client[player_index].player.level, player_index)) {
        dprintf(zappy->server->socket_descriptor->socket_descriptor, "Elevation underway\nCurrent level: %d\n", zappy->client[player_index].player.level);
    } else {
        ai_response_ok_ko(zappy->server->socket_descriptor->socket_descriptor, false);
    }
}

static const ai_request_t ai_request_to_handle[] = {
    {
        .request = "Forward",
        .command = FORWARD,
        .handler = &ai_forward_request
    },
    {
        .request = "Right",
        .command = RIGHT,
        .handler = &ai_right_request
    },
    {
        .request = "Left",
        .command = LEFT,
        .handler = &ai_left_request
    },
    {
        .request = "Look",
        .command = LOOK,
        .handler = &ai_look_request
    },
    {
        .request = "Inventory",
        .command = INVENTORY,
        .handler = &ai_base_request
    },
    {
        .request = "Broadcast text",
        .command = BROADCAST_TEXT,
        .handler = &ai_base_request
    },
    {
        .request = "Connect_nbr",
        .command = CONNECT_NBR,
        .handler = &ai_base_request
    },
    {
        .request = "Fork",
        .command = FORK,
        .handler = &ai_base_request
    },
    {
        .request = "Eject",
        .command = EJECT,
        .handler = &ai_base_request
    },
    {
        .request = "-",
        .command = DEATH,
        .handler = &ai_base_request
    },
    {
        .request = "Take",
        .command = TAKE_OBJECT,
        .handler = &ai_take_request
    },
    {
        .request = "Set",
        .command = SET_OBJECT,
        .handler = &ai_set_request
    },
    {
        .request = "Incantation",
        .command = INCANTATION,
        .handler = &ai_incantation_request
    },
};

char *ai_get_generic_request(int client_socket, zappy_t *zappy, int player_index)
{
    char data[24];
    bzero(data, sizeof(data));
    int read_value = read(client_socket, &data, sizeof(data));

    if (read_value < 0)
        perror("ai_get_generic_request read");
    else if (read_value == 0) {
        close(client_socket);
        zappy->server->server_socket->client[player_index] = 0;
    }

    char *buffer = malloc(sizeof(data));
    strcpy(buffer, data);

    return (buffer);
}

void ai_handle_request(zappy_t *zappy, int player_index)
{
    char *request_data = ai_get_generic_request(zappy->server->socket_descriptor->socket_descriptor, zappy, player_index);

    for (int index = 0; index < NB_COMMANDS_AI; index += 1) {

        if (strncmp(request_data, ai_request_to_handle[index].request, strlen(ai_request_to_handle[index].request)) == 0) {

            printf("handler called: %s\n", ai_request_to_handle[index].request);

            ai_request_to_handle[index].handler(zappy, request_data, player_index);
            return;
        }
    }
}
