/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** map
*/

#ifndef MAP_H_
    #define MAP_H_

    #include <stdio.h>
    #include <stdlib.h>

    #include "zappy/map/resources.h"

typedef struct tile_s {
    int width;
    int heigth;
    resources_t resources;
} tile_t;

typedef struct map_s {
    int width;
    int height;
    int size;
    tile_t **tiles;
} map_t;

void create_map(map_t *map, int width, int height);

void fill_map(map_t *map, resources_t *resource);

void debug_map(map_t *map);
void free_map(map_t *map);

#endif /* !MAP_H_ */
