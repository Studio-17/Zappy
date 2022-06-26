/*
** EPITECH PROJECT, 2022
** project
** File description:
** broadcast_request
*/

#include "ai_request.h"
#include "server.h"
#include <math.h>

void ai_response_broadcast(int socket, char const *message, int orientation)
{
    dprintf(socket, "message %d, %s", orientation, message);
}

int handle_broadcast(zappy_t *zappy, int player_index, position_t origin)
{
    position_t dest = zappy->client[player_index].player.position;
    int orientation = zappy->client[player_index].player.orientation;
    position_t movement = { dest.x - origin.x, dest.y - origin.y };

    if (dest.x == origin.x && dest.y == origin.y)
        return 0;
    float angle = acos((float)abs(movement.x) / sqrt(pow(movement.x, 2) + pow(movement.y, 2)))* (180 / M_PI);
    int res = 0;
    if (angle > 22.5 && angle < 67.5)
        res = 2;
    else if (angle < 22.5)
        res = 1;
    else
        res = 3;
    if (movement.x > 0 && movement.y < 0)
        res += 2;
    else if (movement.x < 0 && movement.y < 0)
        res += 4;
    else if (movement.x < 0 && movement.y > 0)
        res += 6;

    res += 2;
    if (movement.x == 0 || movement.y == 0)
        res += 4;
    res -= 2 * orientation;
    if (res > 8)
        res -= 8;
    if (res <= 0)
        res += 8;
    return res;
}

void ai_broadcast_request(zappy_t *zappy, void *data, int player_index)
{
    char *request = (char *)data;
    int broadcast_len = strlen("Broadcast ");
    int len = strlen(request) - broadcast_len;
    char *message = NULL;

    message = malloc(sizeof(char) * len + 1);
    message[len] = '\0';
    for (int index = broadcast_len; request[index] != '\0'; index++)
        message[index - broadcast_len] = request[index];
    for (int index = 0; index != zappy->server->clients; index++) {
        if (index == player_index)
            continue;
        ai_response_broadcast(zappy->client[index].socket, message, handle_broadcast(zappy, index, zappy->client[player_index].player.position));
    }
    free(message);
    ai_response_ok_ko(zappy->client[player_index].socket, true);
}