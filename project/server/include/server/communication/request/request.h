/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** request
*/

#ifndef REQUEST_H_
    #define REQUEST_H_

    #include "communication/response/response.h"

////////////////////////////////////////////////////////////////////////////////
// AI
////////////////////////////////////////////////////////////////////////////////

enum COMMANDS_AI {
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

typedef struct request_ai_struct {
    enum COMMANDS_AI command;
    char *received;
    int (*func)();
} request_ai;

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

static const request_ai request_ai_list[] = {
    {FORWARD, "Forward", &request_forward},
    {RIGHT, "Right", &request_right},
    {LEFT, "Left", &request_left},
    {LOOK, "Look", &request_look},
    {INVENTORY, "Inventory", &request_inventory},
    {BROADCAST_TEXT, "Broadcast", &request_broadcast_text},
    {CONNECT_NBR, "Connect_nbr", &request_connect_nbr},
    {FORK, "Fork", &request_fork},
    {EJECT, "Eject", &request_eject},
    {DEATH, "", &request_death},
    {TAKE_OBJECT, "Take", &request_take_object},
    {SET_OBJECT, "Set", &request_set_object},
    {INCANTATION, "Incantation", &request_incantation},
};

// COMMANDS_AI

typedef struct command_ai_struct {
    char *action;
    request_ai command;
    float time_limit;
    response_ai response;
} command_ai;

static const command_ai commands_ai[] = {
    {
        .action = "move up one tile",
        .command = request_ai_list[FORWARD],
        .time_limit = 7.0,
        .response = response_ai_list[FORWARD],
    },
    {
        .action = "turn 90° right",
        .command = request_ai_list[RIGHT],
        .time_limit = 7.0,
        .response = response_ai_list[RIGHT],
    },
    {
        .action = "turn 90° left",
        .command = request_ai_list[LEFT],
        .time_limit = 7.0,
        .response = response_ai_list[LEFT],
    },

    {
        .action = "look around",
        .command = request_ai_list[LOOK],
        .time_limit = 7.0,
        .response = response_ai_list[LOOK],
    },
    {
        .action = "invetory",
        .command = request_ai_list[INVENTORY],
        .time_limit = 1.0,
        .response = response_ai_list[INVENTORY],
    },
    {
        .action = "broadcast text",
        .command = request_ai_list[BROADCAST_TEXT],
        .time_limit = 7.0,
        .response = response_ai_list[BROADCAST_TEXT],
    },

    {
        .action = "number of team unused slots",
        .command = request_ai_list[CONNECT_NBR],
        .time_limit = 0.0,
        .response = response_ai_list[CONNECT_NBR],
    },
    {
        .action = "forks a player",
        .command = request_ai_list[FORK],
        .time_limit = 42.0,
        .response = response_ai_list[FORK],
    },
    {
        .action = "eject players from this tile",
        .command = request_ai_list[EJECT],
        .time_limit = 7.0,
        .response = response_ai_list[EJECT],
    },
    {
        .action = "death of a player",
        .command = request_ai_list[DEATH],
        .time_limit = 0.0,
        .response = response_ai_list[DEATH],
    },

    {
        .action = "take object",
        .command = request_ai_list[TAKE_OBJECT],
        .time_limit = 7.0,
        .response = response_ai_list[TAKE_OBJECT],
    },
    {
        .action = "set object down",
        .command = request_ai_list[SET_OBJECT],
        .time_limit = 7.0,
        .response = response_ai_list[SET_OBJECT],
    },
    {
        .action = "start incantation",
        .command = request_ai_list[INCANTATION],
        .time_limit = 300.0,
        .response = response_ai_list[INCANTATION],
    },
};

////////////////////////////////////////////////////////////////////////////////
// GUI
////////////////////////////////////////////////////////////////////////////////

enum COMMANDS_GUI {
    MAP_SIZE,
};

// REQUEST GUI

typedef struct request_gui_struct {
    enum COMMANDS_GUI command;
    char *received;
    int (*func)();
} request_gui;

int request_map_size(void);

// COMMANDS_AI

typedef struct command_gui_struct {
    char *action;
    request_gui command;
    float time_limit;
    response_gui response;
} command_gui;

void handle_request(server_t *server, char *command);

#endif /* !REQUEST_H_ */
