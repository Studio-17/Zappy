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

void ai_base_request(zappy_t *zappy, void *data)
{
    int socket = zappy->server->sd->socket_descriptor;

    write(socket, "UNUSED REQUEST\n", strlen("UNUSED REQUEST\n"));
}

void ai_forward_request(zappy_t *zappy, void *data)
{
    int socket = zappy->server->sd->socket_descriptor;
    position_t player_position = direction[zappy->client[0].player.direction];

    printf("position of player before: %dx, %dy\n", zappy->client[0].player.position.x, zappy->client[0].player.position.y);
    zappy->client[0].player.position.x += player_position.x;
    if (zappy->client[0].player.position.x < 0)
        zappy->client[0].player.position.x = zappy->map->width;
    if (zappy->client[0].player.position.x >= zappy->map->width)
        zappy->client[0].player.position.x = 0;

    zappy->client[0].player.position.y += player_position.y;
    if (zappy->client[0].player.position.y < 0)
        zappy->client[0].player.position.y = zappy->map->height;
    if (zappy->client[0].player.position.y >= zappy->map->height)
        zappy->client[0].player.position.y = 0;
    printf("position of player after: %dx, %dy\n", zappy->client[0].player.position.x, zappy->client[0].player.position.y);
    // write(socket, "FORWARD\n", strlen("FORWARD\n"));
    ai_response_ok_ko(socket, true);
}

void ai_right_request(zappy_t *zappy, void *data)
{
    int socket = zappy->server->sd->socket_descriptor;
    position_t player_position = direction[zappy->client[0].player.direction];

    printf("position of player before: %dx, %dy\n", zappy->client[0].player.position.x, zappy->client[0].player.position.y);
    zappy->client[0].player.direction += 1;
    if (zappy->client[0].player.direction > WEST)
        zappy->client[0].player.direction = NORTH;
    zappy->client[0].player.position.x += player_position.x;
    if (zappy->client[0].player.position.x < 0)
        zappy->client[0].player.position.x = zappy->map->width;
    if (zappy->client[0].player.position.x >= zappy->map->width)
        zappy->client[0].player.position.x = 0;

    zappy->client[0].player.position.y += player_position.y;
    if (zappy->client[0].player.position.y < 0)
        zappy->client[0].player.position.y = zappy->map->height;
    if (zappy->client[0].player.position.y >= zappy->map->height)
        zappy->client[0].player.position.y = 0;
    printf("position of player after: %dx, %dy\n", zappy->client[0].player.position.x, zappy->client[0].player.position.y);

    // write(socket, "RIGHT\n", strlen("RIGHT\n"));
    ai_response_ok_ko(socket, true);
}

void ai_left_request(zappy_t *zappy, void *data)
{
    int socket = zappy->server->sd->socket_descriptor;
    position_t player_position = direction[zappy->client[0].player.direction];

    printf("position of player before: %dx, %dy\n", zappy->client[0].player.position.x, zappy->client[0].player.position.y);
    zappy->client[0].player.direction -= 1;
    if (zappy->client[0].player.direction < NORTH)
        zappy->client[0].player.direction = WEST;
    zappy->client[0].player.position.x += player_position.x;
    if (zappy->client[0].player.position.x < 0)
        zappy->client[0].player.position.x = zappy->map->width;
    if (zappy->client[0].player.position.x >= zappy->map->width)
        zappy->client[0].player.position.x = 0;

    zappy->client[0].player.position.y += player_position.y;
    if (zappy->client[0].player.position.y < 0)
        zappy->client[0].player.position.y = zappy->map->height;
    if (zappy->client[0].player.position.y >= zappy->map->height)
        zappy->client[0].player.position.y = 0;
    printf("position of player after: %dx, %dy\n", zappy->client[0].player.position.x, zappy->client[0].player.position.y);
    // write(socket, "LEFT\n", strlen("LEFT\n"));
    ai_response_ok_ko(socket, true);
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
        .handler = &ai_base_request
    },
    {
        .request = "Set\n",
        .command = SET_OBJECT,
        .handler = &ai_base_request
    },
    {
        .request = "Incantation\n",
        .command = INCANTATION,
        .handler = &ai_base_request
    },
};

char *ai_get_generic_request(int client_socket)
{
    char *data = malloc(sizeof(16));
    int read_value = 0;

    if ((read_value = read(client_socket, data, sizeof(data)) < 0))
        perror("ai_get_generic_request read");

    return (data);
}

void ai_handle_request(zappy_t *zappy)
{
    char *request_data = ai_get_generic_request(zappy->server->sd->socket_descriptor);

    for (int index = 0; index < NB_COMMANDS_AI; index += 1) {

        if (strncmp(request_data, ai_request_to_handle[index].request, strlen(ai_request_to_handle[index].request) - 1) == 0) {

            ai_request_to_handle[index].handler(zappy, NULL);
            return;
        }

    }
}

void ai_response_ok_ko(int socket, bool status)
{
    size_t message_size = 4;

    write(socket, (status ? "ok\n" : "ko\n" ), message_size);
}
