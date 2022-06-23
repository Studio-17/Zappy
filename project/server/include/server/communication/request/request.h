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

    TAKE_OBJECT,
    SET_OBJECT,
    INCANTATION,

    NB_COMMANDS_AI,
};

// REQUEST

typedef void (*ai_request_handler)(zappy_t *, void *, int);

typedef struct ai_request_s {
    char *request;
    enum COMMANDS_AI command;
    ai_request_handler handler;
} ai_request_t;

enum COMMANDS_AI get_command_ai(char *request);

// COMMANDS_AI

typedef struct command_ai_struct {
    char *action;
    enum COMMANDS_AI command;
    float time_limit;
} command_ai;

#endif /* !REQUEST_H_ */
