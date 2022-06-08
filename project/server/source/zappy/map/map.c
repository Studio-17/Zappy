/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** map
*/

#include "zappy/map/map.h"

void create_map(map_t *map, int width, int height)
{
    map->width = width;
    map->height = height;

    map->size = width * height;

    map->tiles = malloc(sizeof(tile_t) * map->height);
    for (int map_height = 0; map_height < map->height; map_height += 1)
        map->tiles[map_height] = malloc(sizeof(tile_t) * map->width);
}

void fill_map(map_t *map, resources_t *resources_list)
{
    int resource = 0;

    for (int map_width = 0; map_width < map->width; map_width += 1) {
        for (int map_height = 0; map_height < map->height; map_height += 1) {
            map->tiles[map_width][map_height].width = map_width;
            map->tiles[map_width][map_height].heigth = map_height;

            map->tiles[map_width][map_height].resources = resources_list[resource];

            // do {
            //     resource = (rand() % NB_ITEMS);
            //     map->tiles[map_width][map_height].resources = resources_list[resource];
            //     resources_list[resource].quantity -= 1;
            // } while (resources_list[resource].quantity <= 0);

        }
    }
}

void debug_map(map_t *map)
{
    printf("map->width: %d\n", map->width);
    printf("map->height: %d\n", map->height);

    printf("map->size: %d\n", map->size);

    for (int map_width = 0; map_width < map->width; map_width += 1) {
        for (int map_height = 0; map_height < map->height; map_height += 1) {
            printf("map->tiles[%d][%d]\n", map->tiles[map_width][map_height].heigth, map->tiles[map_width][map_height].width);
            printf("map->resources: %s\n", map->tiles[map_width][map_height].resources.name);
        }
    }
}

void free_map(map_t *map)
{
    for (int map_width = 0; map_width < map->width; map_width += 1)
        free(map->tiles[map_width]);
    free(map->tiles);

    free(map);
}
