/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** request
*/

#ifndef REQUEST_H_
    #define REQUEST_H_

    #include "communication/response/response.h"

enum COMMANDS {
    FORWARD,
    RIGHT,
    LEFT,

    LOOK,
    INVENTORY,
    BROADCAST_TEXT,

    CONNECT_NBR,
    FORK,
    EJECT,
    DEATH,

    TAKE_OBJECT,
    SET_OBJECT,
    INCANTATION,
};

// REQUEST

typedef struct request_s {
    COMMANDS command;
    char *received;
    int (*func)();
} request_t;

int request_forward(void);
int request_right(void);
int request_left(void);
int request_look(void);
int request_inventory(void);
int request_broadcast_text(void);
int request_connect_nbr(void);
int request_fork(void);
int request_eject(void);
int request_death(void);
int request_take_object(void);
int request_set_object(void);
int request_incantation(void);

static const request_t request_list[] = {
    {COMMANDS::FORWARD, "Forward", &request_forward},
    {COMMANDS::RIGHT, "Right", &request_right},
    {COMMANDS::LEFT, "Left", &request_left},
    {COMMANDS::LOOK, "Look", &request_look},
    {COMMANDS::INVENTORY, "Inventory", &request_inventory},
    {COMMANDS::BROADCAST_TEXT, "Broadcast", &request_broadcast_text},
    {COMMANDS::CONNECT_NBR, "Connect_nbr", &request_connect_nbr},
    {COMMANDS::FORK, "Fork", &request_fork},
    {COMMANDS::EJECT, "Eject", &request_eject},
    {COMMANDS::DEATH, "", &request_death},
    {COMMANDS::TAKE_OBJECT, "Take", &request_take_object},
    {COMMANDS::SET_OBJECT, "Set", &request_set_object},
    {COMMANDS::INCANTATION, "Incantation", &request_incantation},
};

// RESPONSE

typedef struct response_s {
    RESPONSE response;
    int (*func)();
} response_t;

int response_ok(void);
int response_ko(void);
int response_ok_ko(void);
int response_tiles(void);
int response_inventory(void);
int response_value(void);
int response_dead(void);
int response_elevation_underway(void);

static const response_t response_list[] = {
    {RESPONSE::OK, &response_ok},
    {RESPONSE::OK, &response_ok},
    {RESPONSE::OK, &response_ok},
    {RESPONSE::TILES, &response_tiles},
    {RESPONSE::INVENTORY, &response_inventory},
    {RESPONSE::OK, &response_ok},
    {RESPONSE::VALUE, &response_value},
    {RESPONSE::OK, &response_ok},
    {RESPONSE::OK_KO, &response_ok_ko},
    {RESPONSE::DEAD, &response_dead},
    {RESPONSE::OK_KO, &response_ok_ko},
    {RESPONSE::OK_KO, &response_ok_ko},
    {RESPONSE::ELEVATION_UNDERWAY, &response_elevation_underway},
};

// COMMANDS

typedef struct command_s {
    char *action;
    request_t command;
    float time_limit;
    response_t response;
} command_t;

static const command_t commands[] = {
    {
        .action = "move up one tile",
        .command = request_list[COMMANDS::FORWARD],
        .time_limit = 7.0,
        .response = response_list[COMMANDS::FORWARD],
    },
    {
        .action = "turn 90° right",
        .command = request_list[COMMANDS::RIGHT],
        .time_limit = 7.0,
        .response = response_list[COMMANDS::RIGHT],
    },
    {
        .action = "turn 90° left",
        .command = request_list[COMMANDS::LEFT],
        .time_limit = 7.0,
        .response = response_list[COMMANDS::LEFT],
    },

    {
        .action = "look around",
        .command = request_list[COMMANDS::LOOK],
        .time_limit = 7.0,
        .response = response_list[COMMANDS::LOOK],
    },
    {
        .action = "invetory",
        .command = request_list[COMMANDS::INVENTORY],
        .time_limit = 1.0,
        .response = response_list[COMMANDS::INVENTORY],
    },
    {
        .action = "broadcast text",
        .command = request_list[COMMANDS::BROADCAST_TEXT],
        .time_limit = 7.0,
        .response = response_list[COMMANDS::BROADCAST_TEXT],
    },

    {
        .action = "number of team unused slots",
        .command = request_list[COMMANDS::CONNECT_NBR],
        .time_limit = 0.0,
        .response = response_list[COMMANDS::CONNECT_NBR],
    },
    {
        .action = "forks a player",
        .command = request_list[COMMANDS::FORK],
        .time_limit = 42.0,
        .response = response_list[COMMANDS::FORK],
    },
    {
        .action = "eject players from this tile",
        .command = request_list[COMMANDS::EJECT],
        .time_limit = 7.0,
        .response = response_list[COMMANDS::EJECT],
    },
    {
        .action = "death of a player",
        .command = request_list[COMMANDS::DEATH],
        .time_limit = 0.0,
        .response = response_list[COMMANDS::DEATH],
    },

    {
        .action = "take object",
        .command = request_list[COMMANDS::TAKE_OBJECT],
        .time_limit = 7.0,
        .response = response_list[COMMANDS::TAKE_OBJECT],
    },
    {
        .action = "set object down",
        .command = request_list[COMMANDS::SET_OBJECT],
        .time_limit = 7.0,
        .response = response_list[COMMANDS::SET_OBJECT],
    },
    {
        .action = "start incantation",
        .command = request_list[COMMANDS::INCANTATION],
        .time_limit = 300.0,
        .response = response_list[COMMANDS::INCANTATION],
    },
};

#endif /* !REQUEST_H_ */
