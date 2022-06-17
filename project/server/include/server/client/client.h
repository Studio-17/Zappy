/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include "minilib.h"
    #include "listlib.h"

enum CLIENT_TYPE {
    AI,
    GRAPH,
    NB_TYPES,
};

typedef struct position_s {
    int x;
    int y;
} position_t;

typedef struct player_t {
    int id;
    int level;
    int orientation;
    position_t position;
} player_t;

typedef struct ai_client_s {
    int socket;
    int client_nb;
    enum CLIENT_TYPE type;
    player_t player;
} ai_client_t;

typedef struct gui_client_s {
    int socket;
    int client_nb;
    enum CLIENT_TYPE type;
} gui_client_t;

#endif /* !CLIENT_H_ */
