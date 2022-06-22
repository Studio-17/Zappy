/*
** EPITECH PROJECT, 2021
** gameoflife
** File description:
** free_arr
*/

#include <stdlib.h>

void free_arr(char **arr)
{
    for (int i = 0; arr[i] != NULL; i++)
        free(arr[i]);
    free(arr);
}
