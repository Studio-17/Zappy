/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** communication
*/

#include <math.h>

#include "server.h"
#include "ai_request.h"
#include "gui_update.h"
#include "list.h"
#include "request.h"

void death_protocol(zappy_t *zappy, int index)
{
    if (zappy->server->is_gui_connected)
        gui_update_player_dead(zappy, index);

    dprintf(zappy->client[index].socket, "dead\n");

    close(zappy->client[index].socket);
}

void execute_task(list_t *list, zappy_t *zappy, int player_index)
{
    if (queue_is_empty(*list))
        return;

    data_t *request = (data_t *)queue_get_front(*list);

    if (!request->clock) {
        request->clock = clock();
        if (request->request.command == INCANTATION)
            if (!start_incantation(zappy, player_index)) {
                free(request->request.data);
                queue_pop_front(list);
                return;
            }
    }

    clock_t end = clock();

    int millis = (end - request->clock) / 1000;

    if (millis >= (request->request.time_limit * 100 / zappy->options->freq)) {

        request->request.handler(zappy, request->request.data, player_index);

        free(request->request.data);

        queue_pop_front(list);
    }
}

static void consume_time_unit(zappy_t *zappy, int player_index)
{
    clock_t current_time = clock();
    float elapsed_time = (current_time - zappy->client[player_index].clock) / 1000;

    float time_unit_mark = (126.0f / (float)zappy->options->freq) * 100.0f;

    if ( time_unit_mark - elapsed_time <= 0 ) {

        zappy->client[player_index].player.units -= 1;
        zappy->client[player_index].clock = current_time;

    }
}

static void update_food(zappy_t *zappy, int player_index)
{
    if (zappy->client[player_index].player.units == 0) {
        zappy->client[player_index].player.units = 126;
        zappy->client[player_index].player.resource_inventory[FOOD].quantity -= 1;
        gui_update_player_inventory(zappy, player_index);
    }
}

bool listen_clients(zappy_t *zappy)
{
    for (int player_index = 0; player_index < zappy->server->clients; player_index += 1) {

        if (FD_ISSET(zappy->client[player_index].socket, &zappy->server->socket_descriptor->readfd)) {

            ai_request_t request = ai_handle_request(zappy, player_index);

            if (request.command == ERROR)
                return false;
            else if (request.command == OUT_OF_RANGE || request.command == EMPTY)
                continue;
            data_t new_data = {
                .request = request,
                .clock = 0,
            };

            queue_push_back(&zappy->client[player_index].list, &new_data, sizeof(data_t));

            if (check_death(zappy, player_index))
                death_protocol(zappy, player_index);

        }

        update_food(zappy, player_index);

        consume_time_unit(zappy, player_index);

        execute_task(&zappy->client[player_index].list, zappy, player_index);
    }
    return true;
}
