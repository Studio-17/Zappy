/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** connect_nbr._request
*/

#include "ai_request.h"

static int count_team_members(zappy_t *zappy, char *team_name)
{
    int team_members = 0;

    for (int index = 0; index < zappy->server->clients; index += 1) {

        if (strncmp(team_name, zappy->client[index].team_name, strlen(team_name)) == 0) {

            team_members += 1;

        }

    }
    return (team_members);
}

void ai_connect_nbr_request(zappy_t *zappy, __attribute((unused)) void *data, int player_index)
{
    int client_nbr = zappy->options->clients_nb - count_team_members(zappy, zappy->client[player_index].team_name);

    dprintf(zappy->client[player_index].socket, "%d\n", client_nbr);
}
