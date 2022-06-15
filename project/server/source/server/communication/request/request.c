/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** request
*/

#include "server/communication/request/request.h"

static const request_ai request_ai_list[] = {
    {FORWARD, "Forward"},
    {RIGHT, "Right"},
    {LEFT, "Left"},
    {LOOK, "Look"},
    {INVENTORY, "Inventory"},
    {BROADCAST_TEXT, "Broadcast"},
    {CONNECT_NBR, "Connect_nbr"},
    {FORK, "Fork"},
    {EJECT, "Eject"},
    {TAKE_OBJECT, "Take"},
    {SET_OBJECT, "Set"},
    {INCANTATION, "Incantation"},
};

static const command_ai commands_ai[] = {
    {
        .action = "move up one tile",
        .command = FORWARD,
        .time_limit = 7.0,
    },
    {
        .action = "turn 90° right",
        .command = RIGHT,
        .time_limit = 7.0,
    },
    {
        .action = "turn 90° left",
        .command = LEFT,
        .time_limit = 7.0,
    },

    {
        .action = "look around",
        .command = LOOK,
        .time_limit = 7.0,
    },
    {
        .action = "invetory",
        .command = INVENTORY,
        .time_limit = 1.0,
    },
    {
        .action = "broadcast text",
        .command = BROADCAST_TEXT,
        .time_limit = 7.0,
    },

    {
        .action = "number of team unused slots",
        .command = CONNECT_NBR,
        .time_limit = 0.0,
    },
    {
        .action = "forks a player",
        .command = FORK,
        .time_limit = 42.0,
    },
    {
        .action = "eject players from this tile",
        .command = EJECT,
        .time_limit = 7.0,
    },
    {
        .action = "take object",
        .command = TAKE_OBJECT,
        .time_limit = 7.0,
    },
    {
        .action = "set object down",
        .command = SET_OBJECT,
        .time_limit = 7.0,
    },
    {
        .action = "start incantation",
        .command = INCANTATION,
        .time_limit = 300.0,
    },
};

void handle_request(server_t *server, char *command)
{
    printf("[REQUEST] %s\n", command);

    int (*REQUEST[])() = {&request_forward, &request_right, &request_left,
                          &request_look, &request_inventory, &request_broadcast_text,
                          &request_connect_nbr, &request_fork, &request_eject, &request_take_object,
                          &request_set_object, &request_incantation};

    // void (*RESPONSE[])(server_t *, void *) = { &response_ok, &response_ok,
    // &response_ok, &response_tiles, &response_inventory, &response_ok,
    // &response_value, &response_ok, &response_ok_ko, &response_ok_ko,
    // &response_ok_ko, &response_elevation_underway };

    for (int index = 0; index < NB_COMMANDS; index += 1)
    {
        if (strncmp(command, request_ai_list[index].request, strlen(request_ai_list[index].request)) == 0)
        {
            printf("[RESPONSE] %s\n", commands_ai[request_ai_list[index].command].action);
            printf("%d\n", REQUEST[index]());
            // RESPONSE[index](server, NULL);
            return;
        }
    }
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

int request_map_size(void)
{
    return (-1);
}
