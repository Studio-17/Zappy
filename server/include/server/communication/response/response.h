/*
** EPeITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** response
*/

#ifndef RESPONSE_H_
    #define RESPONSE_H_

    #include <stdbool.h>

    #include "server/server.h"

enum RESPONSE {
    OK,
    KO,

    TILES_LIST,
    INVENTORY_LIST,

    VALUE,
    OK_KO,
    DEAD,

    ELEVATION_UNDERWAY,
    CURRENT_LEVEL,
};

typedef struct response_ai_struct {
    enum RESPONSE response;
    int (*func)();
} response_ai;

typedef struct response_elevation_struct {
    bool status;
    int level;
} response_elevation;

#endif /* !RESPONSE_H_ */
