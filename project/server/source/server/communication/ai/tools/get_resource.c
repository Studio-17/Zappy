/*
** EPITECH PROJECT, 2022
** project
** File description:
** tools
*/

#include <stdlib.h>

#include "minilib.h"

int get_resource_from_request(char *target)
{
    char **request_content = my_strtok(target, ' ');
    int length = strlen(request_content[1]);
    char *resource_set[] = {
        "food",
        "linemate",
        "deraumere",
        "sibur",
        "mendiane",
        "phiras",
        "thystame",
        NULL
    };

    if (!request_content)
        return (NULL);
    if (my_arrlen(request_content) != 2)
        return (NULL);
    for (int index = 0; resource_set[index]; index += 1)
        if (strncmp(request_content[1], resource_set[index], length - 2) == 0)
            return (index);
    return (-1);
}
