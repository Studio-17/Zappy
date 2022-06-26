/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** fork_request
*/

#include "ai_request.h"

void ai_fork_request(zappy_t *zappy, void *data, int player_index)
{
    ai_response_ok_ko(zappy->client[player_index].socket, true);
}
