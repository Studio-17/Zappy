/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** my_strtoword
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int count_words(char *str, char sep)
{
    int count = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] != sep && str[i + 1] == sep) {
            count++;
        } else if (str[i] != sep && str[i + 1] == '\0') {
            count++;
        }
    }
    return (count);
}

static bool alloc_my_words(char *str, char **array, char sep)
{
    int x = 0;
    int j = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] != sep)
            x++;
        if ((str[i] != sep && str[i + 1] == sep) ||
            (str[i] != sep && str[i + 1] == 0)) {
            array[j] = malloc(sizeof(char) * (x + 1));
            if (!array[j])
                return false;
            x = 0;
            j++;
        }
        if (j > 0 && !array[j - 1])
            return false;
    }
    return true;
}

static void copy_my_words(char *str, char **array, char sep)
{
    int i = 0;
    int x = 0;

    for (int j = 0; str[j]; j++) {
        if (str[j] != sep) {
            array[i][x] = str[j];
            x++;
        }
        if ((str[j] != sep && str[j + 1] == sep) ||
            (str[j] != sep && str[j + 1] == 0)) {
            array[i][x] = 0;
            i++;
            x = 0;
        }
    }
}

char **my_strtok(char *str, char sep)
{
    int nb_words = count_words(str, sep);
    char **array = malloc(sizeof(char *) * (nb_words + 1));

    if (!array)
        return (NULL);
    array[nb_words] = NULL;
    for (int i = 0; i < nb_words + 1; i++)
        array[i] = NULL;
    if (!alloc_my_words(str, array, sep))
        return (NULL);
    copy_my_words(str, array, sep);
    return (array);
}
