/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** tools
*/

#include <string.h>
#include <stdio.h>

int my_atoi(char *string)
{
    int result = 0;

    for (int index = 0; string[index] != '\0'; index += 1) {
        if (string[index] <= '9' && string[index] >= '0')
            result = result * 10 + string[index] - '0';
        else
            continue;
    }

    if (result < 1)
        return (0);

    return (result);
}

char *my_itoa(int num, char *str)
{
        if(str == NULL)
        {
                return NULL;
        }
        sprintf(str, "%d", num);
        return str;
}
