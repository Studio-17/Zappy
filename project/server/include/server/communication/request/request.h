/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** request
*/

#ifndef REQUEST_H_
    #define REQUEST_H_

    #include "server/server.h"
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
    // DEATH,

    TAKE_OBJECT,
    SET_OBJECT,
    INCANTATION,

    NB_COMMANDS_AI,
};

// REQUEST

typedef struct request_ai_struct {
    enum COMMANDS_AI command;
    char *request;
} request_ai;

enum COMMANDS_AI get_command_ai(char *request);

// COMMANDS_AI

typedef struct command_ai_struct {
    char *action;
    enum COMMANDS_AI command;
    float time_limit;
} command_ai;

////////////////////////////////////////////////////////////////////////////////
// GUI
////////////////////////////////////////////////////////////////////////////////

enum COMMANDS_GUI {
    MAP_SIZE,
    CONTENT_TILE,
    CONTENT_MAP,
    NAME_OF_TEAMS,
    PLAYER_POSITION,
    PLAYER_LEVEL,
    PLAYER_INVENTORY,
    TIME_UNIT,
    TIME_UNIT_MODIFICATION,
    NB_COMMANDS_GUI,
};

// REQUEST GUI

int request_map_size(void);

// COMMANDS_AI

typedef struct command_gui_struct {
    enum COMMANDS_GUI command;
    char *action;
    char *received;
} command_gui;

static const command_gui commands_gui[] = {
    {
        .command = MAP_SIZE,
        .action = "map size\n",
        .received = "msz",
    },
    {
        .command = CONTENT_TILE,
        .action = "content of a file\n",
        .received = "msz",
    },
    {
        .command = CONTENT_MAP,
        .action = "content of the map (all the tiles)\n",
        .received = "bct",
    },
    {
        .command = PLAYER_POSITION,
        .action = "player's position\n",
        .received = "ppo",
    },
    {
        .command = PLAYER_LEVEL,
        .action = "player's level\n",
        .received = "plv",
    },
    {
        .command = PLAYER_INVENTORY,
        .action = "player's inventory\n",
        .received = "pin",
    },
    {
        .command = TIME_UNIT,
        .action = "time unit request\n",
        .received = "sgt",
    },
    {
        .command = TIME_UNIT_MODIFICATION,
        .action = "time unit modification\n",
        .received = "sst",
    },
};

void handle_request(server_t *server, char *command);

#endif /* !REQUEST_H_ */
