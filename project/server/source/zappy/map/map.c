/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** map
*/

#include "zappy/map/map.h"

map_t *create_map(int width, int height)
{
    map_t *map = malloc(sizeof(map_t));
    resources_t const resource_template[] = {
        {.name = "food", .item = FOOD, .density = 0.5, .quantity = 0},
        {.name = "linemate", .item = LINEMATE, .density = 0.3, .quantity = 0},
        {.name = "deraumere", .item = DERAUMERE, .density = 0.15, .quantity = 0},
        {.name = "sibur", .item = SIBUR, .density = 0.1, .quantity = 0},
        {.name = "mendiane", .item = MENDIANE, .density = 0.1, .quantity = 0},
        {.name = "phiras", .item = PHIRAS, .density = 0.08, .quantity = 0},
        {.name = "thystame", .item = THYSTAME, .density = 0.05, .quantity = 0}
    };

    if (!map)
        return NULL;
    map->width = width;
    map->height = height;
    map->size = width * height;
    map->tiles = malloc(sizeof(tile_t) * map->height);
    if (!map->tiles)
        return NULL;
    for (int map_height = 0; map_height < map->height; map_height += 1) {
        map->tiles[map_height] = malloc(sizeof(tile_t) * map->width);
        if (!map->tiles[map_height])
            return NULL;
        for (int map_width = 0; map_width < width; map_width += 1) {
            map->tiles[map_height][map_width].width = map_width;
            map->tiles[map_height][map_width].heigth = map_height;
            map->tiles[map_height][map_width].resources = malloc(sizeof(resources_t) * NB_ITEMS);
            for (int item_index = 0; item_index != NB_ITEMS; item_index += 1)
                map->tiles[map_height][map_width].resources[item_index] = resource_template[item_index];
        }
    }
    return map;
}

void fill_map(map_t *map, resources_t *resources_list)
{
    int quantity = 0;
    float chance = 1;

    for (int resource_index = 0; resource_index != NB_ITEMS; resource_index += 1) {
        quantity = resources_list[resource_index].quantity;
        chance = resources_list[resource_index].density * map->ratio * 100 / 2;
        for (int map_height = 0; map_height < map->height; map_height += 1) {
            for (int map_width = 0; map_width < map->width; map_width += 1) {
                int value = rand() % 100;
                if (value - chance < 0 && quantity > 0) {
                    map->tiles[map_height][map_width].resources[resource_index].quantity += 1;
                    quantity -= 1;
                }
            }
        }
        for (int map_height = map->height - 1; map_height >= 0; map_height -= 1) {
            for (int map_width = map->width - 1; map_width >= 0; map_width -= 1) {
                int value = rand() % 100;
                if (value - chance < 0 && quantity > 0) {
                    map->tiles[map_height][map_width].resources[resource_index].quantity += 1;
                    quantity -= 1;
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

    for (int map_height = 0; map_height < map->height; map_height += 1)
        for (int map_width = 0; map_width < map->width; map_width += 1)
            for (int index = 0; index < NB_ITEMS; index += 1) {
                if (map->tiles[map_height][map_width].resources[index].quantity > 0)
                    printf("[DEBUG] map->tiles[%d][%d].resources[%s]: %d\n", map->tiles[map_height][map_width].heigth, map->tiles[map_height][map_width].width, map->tiles[map_height][map_width].resources[index].name, map->tiles[map_height][map_width].resources[index].quantity);
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
    for (int map_heigth = 0; map_heigth < map->height; map_heigth += 1) {
        for (int map_width = 0; map_width < map->width; map_width += 1) {
            free(map->tiles[map_heigth][map_width].resources);
        }
        free(map->tiles[map_heigth]);
    }
    free(map->tiles);
    free(map);
}
