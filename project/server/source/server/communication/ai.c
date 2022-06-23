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
    int socket = zappy->server->socket_descriptor->socket_descriptor;

    write(socket, "UNUSED REQUEST\n", strlen("UNUSED REQUEST\n"));
}

static const ai_request_t ai_request_to_handle[] = {
    {
        .request = "Forward",
        .command = FORWARD,
        .handler = &ai_forward_request,
        .time_limit = 7,
    },
    {
        .request = "Right",
        .command = RIGHT,
        .handler = &ai_right_request,
        .time_limit = 7,
    },
    {
        .request = "Left",
        .command = LEFT,
        .handler = &ai_left_request,
        .time_limit = 7,
    },
    {
        .request = "Look",
        .command = LOOK,
        .handler = &ai_look_request,
        .time_limit = 7,
    },
    {
        .request = "Inventory",
        .command = INVENTORY,
        .handler = &ai_inventory_request,
        .time_limit = 1,
    },
    {
        .request = "Broadcast text",
        .command = BROADCAST_TEXT,
        .handler = &ai_base_request,
        .time_limit = 7,
    },
    {
        .request = "Connect_nbr",
        .command = CONNECT_NBR,
        .handler = &ai_base_request,
        .time_limit = 0,
    },
    {
        .request = "Fork",
        .command = FORK,
        .handler = &ai_base_request,
        .time_limit = 42,
    },
    {
        .request = "Eject",
        .command = EJECT,
        .handler = &ai_eject_request,
        .time_limit = 7,
    },
    {
        .request = "Take",
        .command = TAKE_OBJECT,
        .handler = &ai_take_request,
        .time_limit = 7,
    },
    {
        .request = "Set",
        .command = SET_OBJECT,
        .handler = &ai_set_request,
        .time_limit = 7,
    },
    {
        .request = "Incantation",
        .command = INCANTATION,
        .handler = &ai_incantation_request,
        .time_limit = 300,
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

static void execute_player_request(list_t list)
{
    data_t *request_data = malloc(sizeof(data_t));

    while (list_get_size(list) != 0) {

        request_data = list_get_elem_at_front(list);

        clock_t timer = clock();
        unsigned long milliseconds_elapsed = (timer - request_data->clock) * 1000 / CLOCKS_PER_SEC;

        if (milliseconds_elapsed >= request_data->request_time * 1000) {

            request_data->request(
                request_data->arguments.structure,
                request_data->arguments.data,
                request_data->arguments.index
            );

            list_del_elem_at_front(&list);

        }
    }
}

bool ai_handle_request(zappy_t *zappy, int player_index)
{
    char *request_data = ai_get_generic_request(zappy->server->socket_descriptor->socket_descriptor, zappy, player_index);
    bool valid_request = false;

    if (!request_data)
        return (false);
    for (int index = 0; index < NB_COMMANDS_AI; index += 1) {

        if (strncmp(request_data, ai_request_to_handle[index].request, strlen(ai_request_to_handle[index].request)) == 0) {

            ai_request_to_handle[index].handler(zappy, request_data, player_index);
            return true;
        }
    }
    ai_response_ok_ko(zappy->client[player_index].socket, false);

    return (true);
}
