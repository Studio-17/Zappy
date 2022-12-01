/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** my_itoa
*/

#include "minilib.h"

char *my_itoa(int number)
{
    int counter = 0;
    int i = number;
    char *string;

    while (i > 0) {
        i /= 10;
        counter++;
    }
    string = malloc(sizeof(4) * (counter + 1));
    string[counter] = '\0';
    while (counter-- != 0) {
        string[counter] = number % 10 + '0';
        number = number / 10;
    }
    return (string);
}
