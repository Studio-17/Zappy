/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** request
*/

#include "server/communication/request/request.h"

static const request_gui request_gui_list[] = {
    {MAP_SIZE, "msz", &request_map_size},
};

static const command_gui commands_gui[] = {
    {
        .action = "map size",
        .command = request_gui_list[MAP_SIZE],
        .time_limit = 0.0,
        .response = response_gui_list[MAP_SIZE],
    },
};

// ERROR HERE

void handle_request(server_t *server, char *command)
{
    for (int index = 0; commands_gui[index]; index += 1) {
        if (strcmp(command, request_gui_list[index].received) == 0) {
            commands_gui[index].response();
            return;
        }
    }
}

int request_map_size(void)
{
    return (42);
}

int request_forward(void)
{
    return (-1);
}

int request_right(void)
{
    return (-1);
}

int request_left(void)
{
    return (-1);
}

int request_look(void)
{
    return (-1);
}

int request_inventory(void)
{
    return (-1);
}

int request_broadcast_text(void)
{
    return (-1);
}

int request_connect_nbr(void)
{
    return (-1);
}

int request_fork(void)
{
    return (-1);
}

int request_eject(void)
{
    return (-1);
}

int request_death(void)
{
    return (-1);
}

int request_take_object(void)
{
    return (-1);
}

int request_set_object(void)
{
    return (-1);
}

int request_incantation(void)
{
    return (-1);
}
