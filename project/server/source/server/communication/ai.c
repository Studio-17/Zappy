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

void ai_base_request(zappy_t *zappy, void *data)
{
    int socket = zappy->server->sd->socket_descriptor;

    write(socket, "RESPONSE\n", strlen("RESPONSE\n"));
}

static const ai_request_t ai_request_to_handle[] = {
    {
        .request = "Forward\n",
        .command = FORWARD,
        .handler = &ai_base_request
    },
    {
        .request = "Right\n",
        .command = RIGHT,
        .handler = &ai_base_request
    },
    {
        .request = "Left\n",
        .command = LEFT,
        .handler = &ai_base_request
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
    char *data = malloc(sizeof(char) * 256);

    if (read(client_socket, data, sizeof(data)) < 0)
        perror("ai_get_generic_request read");

    return (data);
}

void ai_handle_request(zappy_t *zappy)
{
    char *request_data = ai_get_generic_request(zappy->server->sd->socket_descriptor);

    printf("%s", request_data);

    // for (int index = 0; index < NB_COMMANDS_AI; index += 1) {

        // if (strncmp(request_data, ai_request_to_handle[index].request, strlen(request_data)) == 0) {
        //     printf("[FOUDN] %s\n", request_data);
        // }

    // }
}

void ai_response_ok_ko(int socket, bool status)
{
    size_t message_size = 4;

    write(socket, (status ? "ok\n" : "ko\n" ), message_size);
}
