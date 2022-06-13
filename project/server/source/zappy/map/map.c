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
    int ceilling = ceil(map->ratio);

    int resource = 0;
    // int resource_count = 0;

    int count = 0;

    for (int map_width = 0; map_width < map->width; map_width += 1) {
        for (int map_height = 0; map_height < map->height; map_height += 1) {
            map->tiles[map_width][map_height].width = map_width;
            map->tiles[map_width][map_height].heigth = map_height;

            map->tiles[map_width][map_height].resources = malloc(sizeof(resources_t) * ceilling);

            // resource_count = (rand() % ceilling);
            for (int index = 0; index < ceilling; index += 1) {
                resource = (rand() % NB_ITEMS);
                if (resources_list[resource].quantity != 0) {
                    count += 1;
                    map->tiles[map_width][map_height].resources[index] = resources_list[resource];
                    resources_list[resource].quantity -= 1;
                }
            }
        }
    }
}

void debug_map(map_t *map, resources_t *resources_list)
{
    printf("[DEBUG] map->width: %d\n", map->width);
    printf("[DEBUG] map->height: %d\n", map->height);

    printf("[DEBUG] map->size: %f\n", map->size);

    for (int map_width = 0; map_width < map->width; map_width += 1) {
        for (int map_height = 0; map_height < map->height; map_height += 1) {
            for (int index = 0; index < ceil(map->ratio); index += 1) {
                printf("[DEBUG] map->tiles[%d][%d].resources[%d]: %s\n", map->tiles[map_width][map_height].heigth, map->tiles[map_width][map_height].width, index, map->tiles[map_width][map_height].resources[index].name);
            }
        }
    }

    printf("[DEBUG] map->ratio: %f\n", map->ratio);
    printf("[DEBUG] map->ceil = %f\n", ceil(map->ratio));

    int total_items_left = 0;
    for (int index = 0; index < NB_ITEMS; index += 1)
        total_items_left += resources_list[index].quantity;
    printf("[DEBUG] resources_list[ALL].quantity: %d\n", total_items_left);
}

void free_map(map_t *map)
{
    for (int map_width = 0; map_width < map->width; map_width += 1) {
        for (int map_heigth = 0; map_heigth < map->height; map_heigth += 1) {
            free(map->tiles[map_width][map_heigth].resources);
        }
        free(map->tiles[map_width]);
    }
    free(map->tiles);

    free(map);
}
