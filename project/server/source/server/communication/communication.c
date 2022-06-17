/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** communication
*/

#include "server/communication/communication.h"
#include "server/server.h"

void client_sent_request(server_t *server)
{
    return;
}

void handle_client(server_t *server)
{
    for (int index = 0; index < server->ss->max_client; index += 1) {

        server->sd->socket_descriptor = server->ss->client[index];

        // CODE HERE ALL RESPONSE RELATED FUNCTIONS
        // client_sent_request(server);
    }
}
