/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** move
*/

#include "ai_request.h"

void move(zappy_t *zappy, position_t movement, int player_index)
{
    zappy->client[player_index].player.position.x += movement.x;
    if (zappy->client[player_index].player.position.x < 0)
        zappy->client[player_index].player.position.x = zappy->map->width - 1;
    else if (zappy->client[player_index].player.position.x > zappy->map->width - 1)
        zappy->client[player_index].player.position.x = 0;

    zappy->client[player_index].player.position.y += movement.y;
    if (zappy->client[player_index].player.position.y < 0)
        zappy->client[player_index].player.position.y = zappy->map->height - 1;
    else if (zappy->client[player_index].player.position.y > zappy->map->height - 1)
        zappy->client[player_index].player.position.y = 0;
}
