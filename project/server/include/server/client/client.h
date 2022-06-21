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
    #include "netlib.h"

enum CLIENT_TYPE {
    AI,
    GRAPH,
    NB_TYPES,
};

enum DIRECTION {
    DEFAULT = -1,
    NORTH = 0,
    EST = 1,
    SOUTH = 2,
    WEST = 3,
    OUTOFRANGE
};

// enum RESOURCE {
//     FOOD,
//     LINEMATE,
//     DERAUMERE,
//     SIBUR,
//     MENDIANE,
//     PHIRAS,
//     THYSTAME,
//     NB_RESOURCE,
// };

// typedef struct inventory_resource_s {
//     enum RESOURCE resource;
//     int quantity;
// } inventory_resource_t;

typedef struct player_t {
    int id;
    int level;
    position_t position;
    enum DIRECTION orientation;
    // inventory_resource_t resource_inventory[NB_RESOURCE];
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
