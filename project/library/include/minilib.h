/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** minilib
*/

#ifndef MINILIB_H_
    #define MINILIB_H_

    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>

int my_atoi(char *string);
char *my_itoa(int number);

char **my_strtok(char *str, char sep);

#endif /* !MINILIB_H_ */
