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

void ai_forward_request(zappy_t *zappy, void *data, int player_index)
{
    int socket = zappy->server->socket_descriptor->socket_descriptor;
    position_t movement = direction[zappy->client[player_index].player.orientation];

    move(zappy, movement, player_index);
    ai_response_ok_ko(socket, true);
}

void ai_right_request(zappy_t *zappy, void *data, int player_index)
{
    int socket = zappy->server->socket_descriptor->socket_descriptor;
    position_t movement;

    printf("position of player before: %dx, %dy\n", zappy->client[player_index].player.position.x, zappy->client[player_index].player.position.y);
    zappy->client[player_index].player.orientation += 1;
    if (zappy->client[player_index].player.orientation > WEST)
        zappy->client[player_index].player.orientation = NORTH;
    movement = direction[zappy->client[player_index].player.orientation];
    move(zappy, movement, player_index);
    ai_response_ok_ko(socket, true);
}

void ai_left_request(zappy_t *zappy, void *data, int player_index)
{
    int socket = zappy->server->socket_descriptor->socket_descriptor;
    position_t movement;

    printf("position of player before: %dx, %dy\n", zappy->client[player_index].player.position.x, zappy->client[player_index].player.position.y);
    if (zappy->client[player_index].player.orientation < NORTH)
        zappy->client[player_index].player.orientation = WEST;
    else
        zappy->client[player_index].player.orientation -= 1;
    movement = direction[zappy->client[player_index].player.orientation];
    move(zappy, movement, player_index);
    ai_response_ok_ko(socket, true);
}

static char *get_resource_from_request(char *target)
{
    char **request_content = my_strtok(target, ' ');
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
        if (strcmp(request_content[1], resource_set[index]) == 0) {
            printf("Took %s\n", resource_set[index]);
            return (resource_set[index]);
        }
    }
    return (NULL);
}

void ai_take_request(zappy_t *zappy, void *data, int player_index)
{
    char *request = *(char *)data;
    char *resource = get_resource_from_request(request);

    if (resource == NULL)
        ai_response_ok_ko(zappy->server->socket_descriptor->socket_descriptor, false);
    else {
        // code here handler
        ai_response_ok_ko(zappy->server->socket_descriptor->socket_descriptor, true);
    }
}

void ai_set_request(zappy_t *zappy, void *data, int player_index)
{
    char *request = *(char *)data;
    char *resource = get_resource_from_request(request);

    if (resource == NULL)
        ai_response_ok_ko(zappy->server->socket_descriptor->socket_descriptor, false);
    else {
        // code here handler
        ai_response_ok_ko(zappy->server->socket_descriptor->socket_descriptor, true);
    }
}

static const ai_request_t ai_request_to_handle[] = {
    {
        .request = "Forward\n",
        .command = FORWARD,
        .handler = &ai_forward_request
    },
    {
        .request = "Right\n",
        .command = RIGHT,
        .handler = &ai_right_request
    },
    {
        .request = "Left\n",
        .command = LEFT,
        .handler = &ai_left_request
    },
    {
        .request = "Look\n",
        .command = LOOK,
        .handler = &ai_base_request
    },
    {
        .request = "Inventory\n",
        .command = INVENTORY,
        .handler = &ai_base_request
    },
    {
        .request = "Broadcast text\n",
        .command = BROADCAST_TEXT,
        .handler = &ai_base_request
    },
    {
        .request = "Connect_nbr\n",
        .command = CONNECT_NBR,
        .handler = &ai_base_request
    },
    {
        .request = "Fork\n",
        .command = FORK,
        .handler = &ai_base_request
    },
    {
        .request = "Eject\n",
        .command = EJECT,
        .handler = &ai_base_request
    },
    {
        .request = "-\n",
        .command = DEATH,
        .handler = &ai_base_request
    },
    {
        .request = "Take\n",
        .command = TAKE_OBJECT,
        .handler = &ai_take_request
    },
    {
        .request = "Set\n",
        .command = SET_OBJECT,
        .handler = &ai_set_request
    },
    {
        .request = "Incantation\n",
        .command = INCANTATION,
        .handler = &ai_base_request
    },
};

char *ai_get_generic_request(int client_socket, zappy_t *zappy, int player_index)
{
    char *data = malloc(sizeof(16));
    int read_value = read(client_socket, data, sizeof(data));

    if (read_value < 0)
        perror("ai_get_generic_request read");
    else if (read_value == 0) {
        close(client_socket);
        zappy->server->server_socket->client[player_index] = 0;
    }
    return (data);
}

void ai_handle_request(zappy_t *zappy, int player_index)
{
    char *request_data = ai_get_generic_request(zappy->server->socket_descriptor->socket_descriptor, zappy, player_index);

    for (int index = 0; index < NB_COMMANDS_AI; index += 1) {
        if (strncmp(request_data, ai_request_to_handle[index].request, strlen(ai_request_to_handle[index].request) - 1) == 0) {
            ai_request_to_handle[index].handler(zappy, request_data, player_index);
            return;
        }

    }
}
