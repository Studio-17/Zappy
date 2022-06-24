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
    int socket = zappy->client[player_index].socket;

    write(socket, "UNUSED REQUEST\n", strlen("UNUSED REQUEST\n"));
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
        .handler = &ai_inventory_request
    },
    {
        .request = "Broadcast text",
        .command = BROADCAST_TEXT,
        .handler = &ai_base_request
    },
    {
        .request = "Connect_nbr",
        .command = CONNECT_NBR,
        .handler = &ai_connect_nbr_request
    },
    {
        .request = "Fork",
        .command = FORK,
        .handler = &ai_base_request
    },
    {
        .request = "Eject",
        .command = EJECT,
        .handler = &ai_eject_request
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

bool ai_handle_request(zappy_t *zappy, int player_index)
{
    char *request_data = ai_get_generic_request(zappy->client[player_index].socket, zappy, player_index);
    bool valid_request = false;

    if (!request_data)
        return (false);
    for (int index = 0; index < NB_COMMANDS_AI; index += 1) {

        if (strncmp(request_data, ai_request_to_handle[index].request, strlen(ai_request_to_handle[index].request)) == 0) {

            printf("%s handle called\n", ai_request_to_handle[index].request);

            ai_request_to_handle[index].handler(zappy, request_data, player_index);
            valid_request = true;
            return (true);
        }
    }
    if (!valid_request)
        ai_response_ok_ko(zappy->client[player_index].socket, false);

    return (true);
}
