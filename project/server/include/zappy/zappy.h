/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** zappy
*/

#ifndef ZAPPY_H_
    #define ZAPPY_H_

    #include "options/options.h"

    #include "server/server.h"

    #include "zappy/map/map.h"
    #include "zappy/map/resources.h"

typedef struct zappy_s {
    options_t *options;

    server_t *server;

    map_t *map;
    resources_t *ressources;
} zappy_t;

#endif /* !ZAPPY_H_ */
