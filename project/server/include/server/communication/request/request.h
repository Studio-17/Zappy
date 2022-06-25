/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** request
*/

#ifndef REQUEST_H_
    #define REQUEST_H_

    #include "server/server.h"
    #include "server/server_struct.h"
    #include "communication/response/response.h"
    #include "gui_update.h"

////////////////////////////////////////////////////////////////////////////////
// AI
////////////////////////////////////////////////////////////////////////////////

enum COMMANDS_AI {
    EMPTY = -1,
    FORWARD,
    RIGHT,
    LEFT,

    LOOK,
    INVENTORY,
    BROADCAST_TEXT,

    CONNECT_NBR,
    FORK,
    EJECT,

    TAKE_OBJECT,
    SET_OBJECT,
    INCANTATION,
    INVALID,

    NB_COMMANDS_AI,
    ERROR,
    OUT_OF_RANGE,
};

// REQUEST

typedef void (*ai_request_handler)(zappy_t *, void *, int);

typedef struct ai_request_s {
    char *request;
    enum COMMANDS_AI command;
    ai_request_handler handler;
    int time_limit;
    void *data;
} ai_request_t;

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
};

typedef void (*gui_request_handler)(zappy_t *, void *);

void request_map_size(zappy_t *, void *);
void request_tile_content(zappy_t *, void *);
void request_team_names(zappy_t *, void *);
void request_player_connected(zappy_t *, void *);
void request_player_position(zappy_t *, void *);
void request_player_inventory(zappy_t *, void *);
void request_player_level(zappy_t *, void *);
void request_time_unit(zappy_t *, void *);
void request_time_unit_modification(zappy_t *, void *);

typedef struct gui_request_s {
    int type;
    gui_request_handler handler;
} gui_request_t;


typedef void (*request_handler)(void *, void *, int);

// typedef struct argument_handler_s {
//     void *structure;
//     void *data;
//     int index;
// } argument_handler_t;
typedef struct data_s {
    ai_request_t request;
    // argument_handler_t arguments;

    clock_t clock;
} data_t;

ai_request_t ai_handle_request(zappy_t *zappy, int player_index);

// REQUEST HANDLER (with queue)

// typedef struct argument_handler_s {
//     zappy_t *structure;
//     void *data;
//     int index;
// } argument_handler_t;

// typedef struct data_s {
//     ai_request_t request;
//     // argument_handler_t arguments;

//     clock_t clock;
// } data_t;

unsigned int queue_get_size(list_t list);
bool queue_is_empty(list_t list);

bool queue_push_back(list_t *front_ptr, void *elem, int type_size);

bool queue_pop_front(list_t *front_ptr);

void queue_clear(list_t *front_ptr);

void *queue_get_front(list_t list);

#endif /* !REQUEST_H_ */
