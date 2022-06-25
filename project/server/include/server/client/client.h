/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include "minilib.h"
    #include "netlib.h"

enum ORIENTATION {
    DEFAULT = -1,
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3,
    OUTOFRANGE
};

typedef struct gui_client_s {
    int socket;
    int client_nb;
} gui_client_t;

#endif /* !CLIENT_H_ */
