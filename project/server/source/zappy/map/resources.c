/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** resources
*/

#include "zappy/map/map.h"

void setup_resources(resources_t *resource, int width, int height)
{
    for (int index = 0; index < NB_ITEMS ; index += 1)
        resource[index].quantity = RESSOURCE_QUANTITY(width, height, resource[index].density);
}

void debug_resources(resources_t *resource)
{
    for (int index = 0; index < NB_ITEMS ; index += 1) {
        printf("resource.name: %s\n", resource[index].name);
        printf("resource.density: %f\n", resource[index].density);
        printf("resource.quantity: %d\n", resource[index].quantity);
    }
}

void free_ressources(resources_t *resources)
{
    free(resources);
}
