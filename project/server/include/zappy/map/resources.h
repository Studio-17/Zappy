/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** resources
*/

#ifndef RESOURCES_H_
    #define RESOURCES_H_

    #define RESSOURCE_QUANTITY(width, height, density) (width * height * density)

enum ITEM {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    NB_ITEMS,
};

typedef struct resources_s {
    char *name;
    enum ITEM item;
    float density;
    int quantity;
} resources_t;

resources_t *setup_resources(int width, int height);


void debug_resources(resources_t *resource);
void free_resources(resources_t *resources);

#endif /* !RESOURCES_H_ */
