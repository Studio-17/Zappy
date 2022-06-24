/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** communication
*/

#include "server.h"
#include "ai_request.h"
#include "list.h"
#include "request.h"

void death_protocol(zappy_t *zappy, int index)
{
    dprintf(zappy->client[index].socket, "dead\n");
    // disconnect the player
}

int execute_task(list_t *list, zappy_t *zappy, int player_index)
{
    if (queue_is_empty(*list))
        return 0;
    data_t *request = (data_t *)queue_get_front(*list);
    if (!request->clock)
        request->clock = clock();
    clock_t end = clock();
    unsigned long millis = (end - request->clock) / 1000;
    if (millis >= (request->request.time_limit * 100 / zappy->options->freq)) {
        request->request.handler(zappy, request->request.data, player_index);
        printf("time spent: %ld (expected %d)\n", millis / 1000, request->request.time_limit);
        free(request->request.data);
        queue_pop_front(list);
    }
}

bool listen_clients(zappy_t *zappy)
{
    for (int index = 0; index < zappy->server->server_socket->max_client; index += 1) {
        if (FD_ISSET(zappy->server->server_socket->client[index], &zappy->server->socket_descriptor->readfd)) {
            if (!zappy->server->server_socket->client[index])
                continue;
            zappy->server->socket_descriptor->socket_descriptor = zappy->server->server_socket->client[index];

            ai_request_t request = ai_handle_request(zappy, index);

            if (request.command == ERROR)
                return false;
            else if (request.command == OUT_OF_RANGE)
                continue;
                // return true;
            // if (!ai_handle_request(zappy, index))
                // return false;
            data_t new_data = {
                .request = request,
                .clock = 0,
            };
            queue_push_back(&zappy->client[index].list, &new_data, sizeof(data_t));
            printf("queue size %d\n", queue_get_size(zappy->client[index].list));
            if (check_death(zappy, index))
                death_protocol(zappy, index);
        }
        execute_task(&zappy->client[index].list, zappy, index);
    }
    return true;
}
