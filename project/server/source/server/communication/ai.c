/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** ai
*/


#include "server.h"
#include "request.h"
#include "ai_request.h"

void ai_base_request(zappy_t *zappy, void *data, int player_index)
{
    int socket = zappy->server->socket_descriptor->socket_descriptor;

    write(socket, "UNUSED REQUEST\n", strlen("UNUSED REQUEST\n"));
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
        .handler = &ai_look_request
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
    int read_value = 0;

    if (!data)
        return NULL;
    read_value = read(client_socket, data, sizeof(data));
    if (read_value < 0)
        perror("ai_get_generic_request read");
    else if (read_value == 0) {
        close(client_socket);
        zappy->server->server_socket->client[player_index] = 0;
    }
    return (data);
}

bool ai_handle_request(zappy_t *zappy, int player_index)
{
    char *request_data = ai_get_generic_request(zappy->server->socket_descriptor->socket_descriptor, zappy, player_index);

    if (!request_data)
        return false;
    for (int index = 0; index < NB_COMMANDS_AI; index += 1) {
        if (strncmp(request_data, ai_request_to_handle[index].request, strlen(ai_request_to_handle[index].request) - 1) == 0) {
            ai_request_to_handle[index].handler(zappy, request_data, player_index);
            return true;
        }

    }
    return true;
}
