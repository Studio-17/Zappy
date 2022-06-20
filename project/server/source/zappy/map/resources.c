/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** resources
*/

#include <string.h>

#include "zappy/map/map.h"

resources_t *setup_resources(int width, int height)
{
    char const *names[] = { "food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};
    float const density[] = {0.5, 0.3, 0.15, 0.1, 0.1, 0.08, 0.05};
    enum ITEM const items[] = {FOOD, LINEMATE, DERAUMERE, SIBUR, MENDIANE, PHIRAS, THYSTAME};
    resources_t *resource = malloc(sizeof(resources_t) * NB_ITEMS);

    if (!resource)
        return NULL;
    for (int index = 0; index < NB_ITEMS; index += 1) {
        resource[index].name = strdup(names[index]);
        if (!resource[index].name)
            return NULL;
        resource[index].density = density[index];
        resource[index].item = items[index];
        resource[index].quantity = RESSOURCE_QUANTITY(width, height, resource[index].density);
    }
    return resource;
}

void debug_resources(resources_t *resource)
{
    for (int index = 0; index < NB_ITEMS; index += 1)
    {
        printf("[DEBUG] resource.name: %s\n", resource[index].name);
        printf("[DEBUG] resource.density: %f\n", resource[index].density);
        printf("[DEBUG] resource.quantity: %d\n", resource[index].quantity);
    }
}

void free_resources(resources_t *resources)
{
    for (size_t index = 0; index != NB_ITEMS; index++)
        free(resources[index].name);
    free(resources);
}
