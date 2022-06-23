/*
** EPITECH PROJECT, 2022
** project
** File description:
** my_strtab
*/

#include <stdbool.h>
#include <stdlib.h>

int my_strlen(char const *str);

static int get_nbr_rows(char const *str, char delim)
{
    int nb_rows = 1;

    for (int i = 0; str[i]; i++)
        if (str[i] == delim)
            nb_rows++;
    return (nb_rows);
}

static bool alloc_my_words(char const *str, char **array, char sep)
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


static char **fill_map(char const *str, char **ptr, char delim)
{
    int x = 0;
    int y = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != delim) {
            ptr[x][y] = str[i];
            y++;
        }
        else {
            ptr[x][y] = '\0';
            x++;
            y = 0;
        }
    }
    ptr[x][y] = '\0';
    ptr[x + 1] = NULL;
    return (ptr);
}

char **my_str_to_word_arr(char const *str, char delim)
{
    char **ptr = NULL;
    int row = 0;
    int size = 0;

    size = my_strlen(str);
    row = get_nbr_rows(str, delim);
    ptr = malloc(sizeof(char *) * (row + 1));
    if (ptr == NULL)
        return (NULL);
    for (int i = 0; i < row; i++) {
        ptr[i] = malloc(sizeof(char) * (size + 1));
        if (ptr[i] == NULL)
            return (NULL);
    }
    ptr = fill_map(str, ptr, delim);
    return (ptr);
}