/*
** EPITECH PROJECT, 2022
** project
** File description:
** zappy
*/

#include <stdlib.h>

#include "server.h"

zappy_t *init_zappy(void)
{
    zappy_t *zappy = malloc(sizeof(zappy_t));

    if (!zappy)
        return NULL;
    zappy->options = malloc(sizeof(options_t));
    if (!zappy->options) {
        free(zappy->options);
        return NULL;
    }
    setup_options(zappy->options);
    return zappy;
}