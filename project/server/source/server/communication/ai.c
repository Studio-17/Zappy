/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** ai
*/

#include "server.h"
#include "request.h"
#include "ai_request.h"


void ai_base_request(zappy_t *zappy, __attribute__((unused)) void *data, __attribute__((unused))int player_index)
{
    int socket = zappy->client[player_index].socket;

    write(socket, "UNUSED REQUEST\n", strlen("UNUSED REQUEST\n"));
}

static const ai_request_t ai_request_to_handle[] = {
    {
        .request = "Forward",
        .command = FORWARD,
        .handler = &ai_forward_request,
        .time_limit = 7,
        .data = NULL,
    },
    {
        .request = "Right",
        .command = RIGHT,
        .handler = &ai_right_request,
        .time_limit = 7,
        .data = NULL,
    },
    {
        .request = "Left",
        .command = LEFT,
        .handler = &ai_left_request,
        .time_limit = 7,
        .data = NULL,
    },
    {
        .request = "Look",
        .command = LOOK,
        .handler = &ai_look_request,
        .time_limit = 7,
        .data = NULL,
    },
    {
        .request = "Inventory",
        .command = INVENTORY,
        .handler = &ai_inventory_request,
        .time_limit = 1,
        .data = NULL,
    },
    {
        .request = "Broadcast text",
        .command = BROADCAST_TEXT,
        .handler = &ai_base_request,
        .time_limit = 7,
        .data = NULL,
    },
    {
        .request = "Connect_nbr",
        .command = CONNECT_NBR,
        .handler = &ai_connect_nbr_request,
        .time_limit = 0,
        .data = NULL,
    },
    {
        .request = "Fork",
        .command = FORK,
        .handler = &ai_base_request,
        .time_limit = 42,
        .data = NULL,
    },
    {
        .request = "Eject",
        .command = EJECT,
        .handler = &ai_eject_request,
        .time_limit = 7,
        .data = NULL,
    },
    {
        .request = "Take",
        .command = TAKE_OBJECT,
        .handler = &ai_take_request,
        .time_limit = 7,
        .data = NULL,
    },
    {
        .request = "Set",
        .command = SET_OBJECT,
        .handler = &ai_set_request,
        .time_limit = 7,
        .data = NULL,
    },
    {
        .request = "Incantation",
        .command = INCANTATION,
        .handler = &ai_incantation_request,
        .time_limit = 300,
        .data = NULL,
    },
    {
        .request = "",
        .command = INVALID,
        .handler = &ai_invalid_request,
        .time_limit = 0,
        .data = NULL,
    }
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

ai_request_t ai_handle_request(zappy_t *zappy, int player_index)
{
    char *request_data = ai_get_generic_request(zappy->client[player_index].socket, zappy, player_index);
    bool valid_request = false;
    ai_request_t tmp;
    ai_request_t error_request = { .command = ERROR };
    ai_request_t out_of_range_request = { .command = OUT_OF_RANGE };

    if (!request_data)
        return (error_request);
    if (queue_get_size(zappy->client[player_index].list) >= 10) {
        printf("out of range\n");
        return (out_of_range_request);
    }
    for (int index = 0; index < NB_COMMANDS_AI; index += 1) {
        if (strncmp(request_data, ai_request_to_handle[index].request, strlen(ai_request_to_handle[index].request)) == 0) {
            tmp = ai_request_to_handle[index];
            tmp.data = strdup(request_data);
            return tmp;
        }
    }
    ai_response_ok_ko(zappy->client[player_index].socket, false);

    return (ai_request_to_handle[INVALID]);
}
