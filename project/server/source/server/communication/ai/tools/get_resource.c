/*
** EPITECH PROJECT, 2022
** project
** File description:
** tools
*/

#include <stdlib.h>

#include "minilib.h"

char *get_resource_from_request(char *target)
{
    char **request_content = my_strtok(target, ' ');
    char *resource_set[] = {
        "Food",
        "Linemate",
        "Deraumere",
        "Sibur",
        "Mendiane",
        "Phiras",
        "Thystame",
        NULL
    };

    if (!request_content)
        return (NULL);
    if (my_arrlen(request_content) != 2)
        return (NULL);
    for (int index = 0; resource_set[index]; index += 1) {
        if (strcmp(request_content[1], resource_set[index]) == 0) {
            printf("Took %s\n", resource_set[index]);
            return (resource_set[index]);
        }
    }
    return (NULL);
}